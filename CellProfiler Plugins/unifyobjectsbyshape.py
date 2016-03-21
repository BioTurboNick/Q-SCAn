'''<b>Unify Objects By Shape</b>
<hr>

This is a special implementation of <b>ReassignObjectNumbers</b> which uses
a method to join object pairs together which share extensive contacts and form
a convex surface against the background or other objects.

For each pair of adjacent objects, the algorithm identifies vertices for
the pair--a pixel in the first object which is adjacent to a pixel in the second object
and also adjacent to a pixel which doesn't belong to either object.

Then the number of pixels around each vertex within the window size which do not belong
to the object pair are counted and divided by the number of pixels expected if the vertex
was part of a flat surface across the two objects, which would give a score of 0.5. The
maximum vertex score for the object pair is saved.
<ul>
<li>&lt;0.5: The objects curve away from the background (convex).</li>
<li>0.5: The object surface is flat with respect to the background.</li>
<li>&gt;0.5: The objects curve into from the background (concave).</li>
</ul>

Next, the algorithm asks how extensive the contacts are between the two objects. It does
this by calculating the perimeter of each object separately and then of the potential
merged object, subtracting them and dividing by two. This value is then divided by the
sum of the value and the 'diameter' of the smaller object, this 'diameter' calculated based
on a circle with the same perimeter as the smaller object. Large values (> 0.5) indicate
extensive contact.

These two scores, the maximum vertex score and shared extent score, are averaged to
produce the final score. If this score is greater than the threshold value, the object pair
is merged. This merged pair is then compared against all of their neighbors until all possible
merges have occured.

This module can take a long time if the number of touching objects is extensive.
'''
# CellProfiler is distributed under the GNU General Public License.
# See the accompanying file LICENSE for details.
# 
# Copyright (c) 2003-2009 Massachusetts Institute of Technology
# Copyright (c) 2009-2012 Broad Institute
# 
# Please see the AUTHORS file for credits.
# 
# Website: http://www.cellprofiler.org
#
# #################################################################
#
# UnifyObjectsByShape Copyright (c) 2012-2013 Emory University
# Written by Nicholas Bauer


__version__="$Revision$"

import numpy as np
import scipy.ndimage as scind

import cellprofiler.cpmodule as cpm
import cellprofiler.measurements as cpmeas
import cellprofiler.objects as cpo
import cellprofiler.settings as cps
import cellprofiler.cpimage as cpi
import cellprofiler.preferences as cpprefs
from cellprofiler.modules.identify import get_object_measurement_columns
from cellprofiler.modules.identify import add_object_count_measurements
from cellprofiler.modules.identify import add_object_location_measurements
from cellprofiler.modules.identify import C_PARENT, C_CHILDREN
from cellprofiler.modules.identify import FF_CHILDREN_COUNT, FF_PARENT
import cellprofiler.cpmath.cpmorphology as morph
from cellprofiler.cpmath.filter import stretch
import cellprofiler.cpmath.outline

class UnifyObjectsByShape(cpm.CPModule):
    module_name = "UnifyObjectsByShape"
    category = "Object Processing"
    variable_revision_number = 1
    
    def create_settings(self):
        self.objects_name = cps.ObjectNameSubscriber(
            "Select the input objects",
            "None",
            doc="""Select the objects whose object numbers you want to reassign.
            You can use any objects that were created in previous modules, such as 
            <b>IdentifyPrimaryObjects</b> or <b>IdentifySecondaryObjects</b>.""")
        # Note: Above default should change to cps.NONE when the new revision is distributed.

        self.output_objects_name = cps.ObjectNameProvider(
            "Name the new objects","RelabeledCells",
            doc="""What do you want to call the objects whose numbers have been reassigned?
            You can use this name in subsequent
            modules that take objects as inputs.""")
        
        self.window_size = cps.Integer("Window size", 10,
            doc = """Enter how big the search window should be. The window will be
            a square of (2 * window size) + 1 on each side.""")

        self.threshold = cps.Float("Threshold", 0.5,
            doc = """Enter the threshold to be used. Generally this should remain at or near 0.5.""")
        
        self.wants_outlines = cps.Binary(
            "Retain outlines of the relabeled objects?", False,
            doc = """<i>(Used only if objects are output)</i><br>
            Check this setting if you want to save an image of the outlines
            of the relabeled objects.""")
        
        self.outlines_name = cps.OutlineNameProvider(
            'Name the outlines',
            'RelabeledCellOutlines',
            doc = """<i>(Used only if outlines are to be retained)</i><br>
            Enter a name that will allow the outlines to be selected later in the pipeline.""")

    def settings(self):
        return [self.objects_name, self.output_objects_name,
                self.wants_outlines, self.outlines_name,
                self.window_size, self.threshold]
    
    def visible_settings(self):
        result = [self.objects_name, self.output_objects_name]
        result += [self.window_size, self.threshold]
        result += [self.wants_outlines]
        if self.wants_outlines:
            result += [self.outlines_name]
        return result
    
    def is_interactive(self):
        return False
    
    def run(self, workspace):
        objects = workspace.object_set.get_objects(self.objects_name.value)
        assert isinstance(objects, cpo.Objects)
        labels = objects.segmented
        half_window_size = self.window_size.value
        threshold = self.threshold.value
        output_labels = objects.segmented.copy()
        max_objects = np.max(output_labels)
        indices = np.arange(max_objects+1)

        # Get object slices
        object_slices = morph.fixup_scipy_ndimage_result(scind.measurements.find_objects(output_labels))

        # Calculate perimeters
        perimeters = morph.calculate_perimeters(output_labels, indices)

        # Find the neighbors
        neighbors = np.zeros((max_objects+1, max_objects+1), bool) # neighbors[i,j] = True when object j is a neighbor of object i.
        lmax = scind.grey_dilation(output_labels, footprint=np.ones((3,3), bool)) # lower pixel values will be replaced by adjacent larger pixel values
        lbig = output_labels.copy()
        lbig[lbig == 0] = np.iinfo(output_labels.dtype).max # set the background to be large so that it is ignored next
        lmin = scind.grey_erosion(lbig, footprint=np.ones((3,3), bool)) # larger pixel values will be replaced by adjacent smaller pixel values
        
        for i in range(1, max_objects+1):
            object_bounds = (object_slices[i-1][0],object_slices[i-1][1])
            object_map = output_labels[object_bounds] == i # The part of the slice that contains the object
            
            lower_neighbors = np.unique(lmin[object_bounds][object_map])
            higher_neighbors = np.unique(lmax[object_bounds][object_map])

            for neighbor_list in [lower_neighbors, higher_neighbors]:
                for j in range(0, len(neighbor_list)):
                    neighbors[i,neighbor_list[j]] = True
            neighbors[i,i] = False
        
        # Generate window dimensions for each location (necessary for the edges)
        dim1_window = np.ones(output_labels.shape, int) * half_window_size
        dim2_window = np.ones(output_labels.shape, int) * half_window_size
        for i in range(0, half_window_size):
            dim1_window[i:output_labels.shape[0]-i,0:output_labels.shape[1]] += 1
            dim2_window[0:output_labels.shape[0],i:output_labels.shape[1]-i] += 1
        
        # Loop over all objects
        for k in range(1, max_objects+1):
            if (perimeters[k] == 0) or not np.max(neighbors[k]): # Has been removed by a merge or has no neighbors
                continue

            k_bounds_array = object_slices[k-1]
            k_dim1_bounds = k_bounds_array[0].indices(output_labels.shape[0])
            k_dim2_bounds = k_bounds_array[1].indices(output_labels.shape[1])
            
            # Loop over all neighbors of object k
            l = 0
            while l < max_objects:
                l += 1
                
                if k == l or (perimeters[l] == 0) or not neighbors[k,l]: # Has been removed by a merge or is not a neighbor of object k
                    continue

                l_bounds_array = object_slices[l-1]
                l_dim1_bounds = l_bounds_array[0].indices(output_labels.shape[0])
                l_dim2_bounds = l_bounds_array[1].indices(output_labels.shape[1])

                kl_dim1_min_bound = min(k_dim1_bounds[0], l_dim1_bounds[0])
                kl_dim1_max_bound = max(k_dim1_bounds[1], l_dim1_bounds[1])
                kl_dim2_min_bound = min(k_dim2_bounds[0], l_dim2_bounds[0])
                kl_dim2_max_bound = max(k_dim2_bounds[1], l_dim2_bounds[1])

                kl_bounds = (slice(kl_dim1_min_bound, kl_dim1_max_bound), slice(kl_dim2_min_bound, kl_dim2_max_bound))
                kl_shape = (kl_dim1_max_bound - kl_dim1_min_bound, kl_dim2_max_bound - kl_dim2_min_bound)
                
                #
                # Find the vertices of object pair k, l
                #
                vertices = np.zeros(kl_shape, bool)
                isAdjacent = np.zeros(output_labels.shape, bool)
                isBorder = np.zeros(output_labels.shape, bool)
                
                for i in range(-1,2):
                    ki_min = 0
                    ki_max = 0
                    li_min = 0
                    li_max = 0
                    if k_dim1_bounds[0] + i < 0:
                        ki_min = -i
                    else:
                        ki_min = k_dim1_bounds[0]

                    if l_dim1_bounds[0] + i < 0:
                        li_min = -i
                    else:
                        li_min = l_dim1_bounds[0]

                    if k_dim1_bounds[1] + i > output_labels.shape[0]:
                        ki_max = output_labels.shape[0] - i
                    else:
                        ki_max = k_dim1_bounds[1]

                    if l_dim1_bounds[1] + i > output_labels.shape[0]:
                        li_max = output_labels.shape[0] - i
                    else:
                        li_max = l_dim1_bounds[1]

                    ki_slice = slice(ki_min, ki_max)
                    li_slice = slice(li_min, li_max)
                    ki_test_slice = slice(ki_min+i, ki_max+i)
                    li_test_slice = slice(li_min+i, li_max+i)
                    
                    for j in range(-1,2):
                        if i == j == 0:
                            continue

                        kj_min = 0
                        kj_max = 0
                        lj_min = 0
                        lj_max = 0
                        if k_dim2_bounds[0] + j < 0:
                            kj_min = -j
                        else:
                            kj_min = k_dim2_bounds[0]

                        if l_dim2_bounds[0] + j < 0:
                            lj_min = -j
                        else:
                            lj_min = l_dim2_bounds[0]

                        if k_dim2_bounds[1] + j > output_labels.shape[0]:
                            kj_max = output_labels.shape[0] - j
                        else:
                            kj_max = k_dim2_bounds[1]

                        if l_dim2_bounds[1] + j > output_labels.shape[0]:
                            lj_max = output_labels.shape[0] - j
                        else:
                            lj_max = l_dim2_bounds[1]

                        if (kj_min == kj_max or ki_min == ki_max) and (lj_min == lj_max or li_min == li_max):
                            continue

                        kj_slice = slice(kj_min, kj_max)
                        lj_slice = slice(lj_min, lj_max)
                        kj_test_slice = slice(kj_min+j, kj_max+j)
                        lj_test_slice = slice(lj_min+j, lj_max+j)

                        k_bounds = (ki_slice, kj_slice)
                        l_bounds = (li_slice, lj_slice)
                        k_test_bounds = (ki_test_slice, kj_test_slice)
                        l_test_bounds = (li_test_slice, lj_test_slice)
                        kl_mod_bounds = (slice(min(ki_min, li_min), max(ki_max, li_max)), slice(min(kj_min, lj_min), max(kj_max, lj_max)))

                        isAdjacentSlice = np.zeros(output_labels.shape, bool)
                        isAdjacentSlice[k_bounds] = np.logical_and(output_labels[k_bounds] == k,
                                                                   output_labels[k_test_bounds] == l)
                        isAdjacentSlice[l_bounds] = np.logical_or(isAdjacentSlice[l_bounds],
                                                                  np.logical_and(output_labels[l_bounds] == l,
                                                                                 output_labels[l_test_bounds] == k))
                        isAdjacent[kl_mod_bounds] = np.logical_or(isAdjacent[kl_mod_bounds],
                                                                  isAdjacentSlice[kl_mod_bounds])

                        isBorderSlice = np.zeros(output_labels.shape, bool)
                        isBorderSlice[k_bounds] = np.logical_and(output_labels[k_bounds] == k,
                                                                 np.logical_and(output_labels[k_test_bounds] != k,
                                                                                output_labels[k_test_bounds] != l))
                        isBorderSlice[l_bounds] = np.logical_or(isBorderSlice[l_bounds],
                                                                np.logical_and(output_labels[l_bounds] == l,
                                                                               np.logical_and(output_labels[l_test_bounds] != k,
                                                                                              output_labels[l_test_bounds] != l)))
                        isBorder[kl_mod_bounds] = np.logical_or(isBorder[kl_mod_bounds],
                                                                isBorderSlice[kl_mod_bounds])
                
                vertices = np.logical_and(isAdjacent[kl_bounds], isBorder[kl_bounds])

                #
                # Calculate the maximum vertex score for the pair
                #
                '''+1 for every non-I/J labeled pixel in the window
                +1 more for every non-I/J labeled pixel adjacent to it

                Divided by the score that would result if the objects were flat

                e.g. (vertex is starred)

                0  0  0  0  0  0  0
                0  0  0  0  0  0  0
                1  1  0  0  0  0  0
                1  1  1 *1* 2  2  0
                1  1  1  1  2  2  2
                1  1  1  1  2  2  2
                1  1  1  2  2  2  2

                If it were flat, it would be 7 * 3 = 21, so the divisor 7 * 6 = 42.
                In the case that the window is rectangular (such as at the image edge),
                we split the difference.
                Generalized:

                Vertex Score = (Sum of NotIJ) / [A * B - 0.5 * (A + B)]
                '''
                
                sum_not_IJ = np.zeros(kl_shape, int)
                for i in range(0, kl_shape[0]):
                    for j in range(0,kl_shape[1]):
                        if not vertices[i,j]:
                            continue

                        window_bounds = (slice(i - half_window_size + kl_dim1_min_bound, i + half_window_size + kl_dim1_min_bound),
                                         slice(j - half_window_size + kl_dim2_min_bound, j + half_window_size + kl_dim2_min_bound))

                        window_slice = output_labels[window_bounds]

                        sum_not_IJ[i,j] = count_nonzero(np.logical_and(window_slice != k,
                                                                     window_slice != l))
                        # Should be np.count_nonzero, but it doesn't exist in the version that comes with
                        # CellProfiler 2.0 r11710

                vertex_scores = sum_not_IJ / (dim1_window[kl_bounds] * dim2_window[kl_bounds] - 0.5 * (dim1_window[kl_bounds] + dim2_window[kl_bounds]))

                merged = np.zeros(kl_shape, int)
                merged[output_labels[kl_bounds] == k] = 1
                merged[output_labels[kl_bounds] == l] = 1

                merged_perimeter = morph.calculate_perimeters(merged, [1])

                seam_length = (perimeters[k] + perimeters[l] - merged_perimeter) / 2
                min_external_perimeter = min(perimeters[k], perimeters[l]) - seam_length
                adjusted_min_external_perimeter = min_external_perimeter / np.pi

                seam_fraction = seam_length / (adjusted_min_external_perimeter + seam_length)
                
                max_vertex_score = np.max(vertex_scores)

                score = (max_vertex_score + seam_fraction) / 2

                #
                # Join object pair with score above the threshold
                #
                if score >= threshold:
                    output_labels[output_labels == l] = k
                    
                    # Calculate new perimeters
                    perimeters[k] = merged_perimeter
                    perimeters[l] = 0

                    # Reconfigure neighbors
                    neighbors[k] = np.logical_or(neighbors[k], neighbors[l])
                    for x in range(1, max_objects+1): # Is there an array method to do this?
                        if neighbors[x,l]:
                            neighbors[x,k] = True
                    neighbors[0:max_objects,l] = False

                    # Recalculate bounds
                    k_dim1_bounds = kl_bounds[0].indices(output_labels.shape[0])
                    k_dim2_bounds = kl_bounds[1].indices(output_labels.shape[1])
                    
                    # Reset l to 0 so that we check all the neighbors against this new object
                    l = 0
                else:
                    pass
                        
        output_objects = cpo.Objects()
        output_objects.segmented = output_labels
        if objects.has_small_removed_segmented:
            output_objects.small_removed_segmented = \
                copy_labels(objects.small_removed_segmented, output_labels)
        if objects.has_unedited_segmented:
            output_objects.unedited_segmented = \
                copy_labels(objects.unedited_segmented, output_labels)
        output_objects.parent_image = objects.parent_image
        workspace.object_set.add_objects(output_objects, self.output_objects_name.value)
        
        measurements = workspace.measurements
        add_object_count_measurements(measurements,
                                      self.output_objects_name.value,
                                      np.max(output_objects.segmented))
        add_object_location_measurements(measurements,
                                         self.output_objects_name.value,
                                         output_objects.segmented)
        
        #
        # Relate the output objects to the input ones and record
        # the relationship.
        #
        children_per_parent, parents_of_children = \
            objects.relate_children(output_objects)
        measurements.add_measurement(self.objects_name.value,
                                     FF_CHILDREN_COUNT % 
                                     self.output_objects_name.value,
                                     children_per_parent)
        measurements.add_measurement(self.output_objects_name.value,
                                     FF_PARENT%self.objects_name.value,
                                     parents_of_children)
        if self.wants_outlines:
            outlines = cellprofiler.cpmath.outline.outline(output_labels)
            outline_image = cpi.Image(outlines.astype(bool))
            workspace.image_set.add(self.outlines_name.value,
                                    outline_image)
                    
        if workspace.frame is not None:
            workspace.display_data.orig_labels = objects.segmented
            workspace.display_data.output_labels = output_objects.segmented        
    
    def display(self, workspace):
        '''Display the results of relabeling
        
        workspace - workspace containing saved display data
        '''
        from cellprofiler.gui.cpfigure import renumber_labels_for_display
        import matplotlib.cm as cm
        
        figure = workspace.create_or_find_figure(title="UnifyObjectsByShape, image cycle #%d"%(
                workspace.measurements.image_set_number),subplots=(1,2))
        figure.subplot_imshow_labels(0,0, workspace.display_data.orig_labels,
                                     title = self.objects_name.value)
        
        output_labels = renumber_labels_for_display(
                workspace.display_data.output_labels)
        objects = workspace.object_set.get_objects(self.objects_name.value)
        labels = objects.segmented
        image = labels.astype(float) / (1.0 if np.max(labels) == 0 else np.max(labels))
        image = (stretch(image) * 255).astype(np.uint8)  
        
        image = np.dstack((image,image,image))
        my_cm = cm.get_cmap(cpprefs.get_default_colormap())
        my_cm.set_bad((0,0,0))
        sm = cm.ScalarMappable(cmap=my_cm)
        m_output_labels = np.ma.array(output_labels,
                                    mask = output_labels == 0)
        output_image = sm.to_rgba(m_output_labels, bytes=True)[:,:,:3]
        image[output_labels > 0 ] = (
            image[output_labels > 0] / 4 * 3 +
            output_image[output_labels > 0,:] / 4)
    
        figure.subplot_imshow(0,1, image,
                              title = self.output_objects_name.value,
                              sharex = figure.subplot(0,0),
                              sharey = figure.subplot(0,0))
        
    def get_measurement_columns(self, pipeline):
        columns =  get_object_measurement_columns(self.output_objects_name.value)
        columns += [(self.output_objects_name.value,
                     FF_PARENT % self.objects_name.value,
                     cpmeas.COLTYPE_INTEGER),
                    (self.objects_name.value,
                     FF_CHILDREN_COUNT % self.output_objects_name.value,
                     cpmeas.COLTYPE_INTEGER)]
        return columns
    
    def get_categories(self,pipeline, object_name):
        """Return the categories of measurements that this module produces
        
        object_name - return measurements made on this object (or 'Image' for image measurements)
        """
        if object_name == 'Image':
            return ['Count']
        elif object_name == self.output_objects_name.value:
            return ['Location','Parent','Number']
        elif object_name == self.objects_name.value:
            return ['Children']
        return []
      
    def get_measurements(self, pipeline, object_name, category):
        """Return the measurements that this module produces
        
        object_name - return measurements made on this object (or 'Image' for image measurements)
        category - return measurements made in this category
        """
        if object_name == 'Image' and category == 'Count':
            return [ self.output_objects_name.value ]
        elif object_name == self.output_objects_name.value and category == 'Location':
            return ['Center_X','Center_Y']
        elif object_name == self.output_objects_name.value and category == 'Parent':
            return [ self.objects_name.value]
        elif object_name == self.output_objects_name.value and category == 'Number':
            return ['Object_Number']
        elif object_name == self.objects_name.value and category == 'Children':
            return [ "%s_Count" % self.output_objects_name.value]
        return []

def count_nonzero(labels):
    '''Old version of NumPy with CellProfiler r11710 doesn't have this, so we'll just fake it.'''
    count_labels = np.zeros(labels.shape, int)
    count_labels[labels > 0] = 1
    count = np.sum(count_labels)
    return count

def copy_labels(labels, segmented):
    '''Carry differences between orig_segmented and new_segmented into "labels"
    
    labels - labels matrix similarly segmented to "segmented"
    segmented - the newly numbered labels matrix (a subset of pixels are labeled)
    '''
    max_labels = np.max(segmented)
    seglabel = scind.minimum(labels, segmented, np.arange(1, max_labels+1))
    labels_new = labels.copy()
    labels_new[segmented != 0] = seglabel[segmented[segmented != 0] - 1]
    return labels_new
