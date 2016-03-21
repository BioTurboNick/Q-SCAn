CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130716190332

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the DIC image and any fluorescence images used to supplement it. Also extract metadata about the image.\'\x5D|batch_state:array(\'\', \n      dtype=\'\x7CS1\')]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:Median
    Analyze all subfolders within the selected folder?:All
    Input image file location:Default Input Folder sub-folder\x7CCorrected Images
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:No
    Specify metadata fields to group by:
    Select subfolders to analyze:
    Image count:3
    Text that these images have in common (case-sensitive):ChD-T3
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:DIC
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch2-T3
    Position of this image in each group:3
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:MTSmCer
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch3-T1
    Position of this image in each group:3
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:NLStdTom
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:Yes

Smooth:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Subtly smooth the DIC image to remove noise that interferes with downstream processing steps. Edge preservation is important for the next steps. The edge intensity difference is empirically-determined, and would necessarily be dependent on the DIC images taken.\'\x5D|batch_state:array(\'\', \n      dtype=\'\x7CS1\')]
    Select the input image:DIC
    Name the output image:DICSmoothed
    Select smoothing method:Smooth Keeping Edges
    Calculate artifact diameter automatically?:Yes
    Typical artifact diameter, in  pixels:10
    Edge intensity difference:0.01

EnhanceEdges:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'This module finds the edges in the smoothed DIC image using the Laplacian of Gaussian method. This provides a second way of extracting cell information from the DIC image which is complementary too the prior method.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICSmoothed
    Name the output image:DICSmoothedEdged
    Automatically calculate the threshold?:Yes
    Absolute threshold:0.2
    Threshold adjustment factor:1
    Select an edge-finding method:LoG
    Select edge direction to enhance:All
    Calculate Gaussian\'s sigma automatically?:Yes
    Gaussian\'s sigma value:1
    Calculate value for low threshold automatically?:Yes
    Low threshold value:0.1

EnhanceOrSuppressFeatures:[module_num:4|svn_version:\'Unknown\'|variable_revision_number:4|show_window:False|notes:\x5B\'Same idea as the previous EnhanceOrSuppressFeatures module, but using the edged DIC image instead of the DIC image itself. Fewer internal bright spots exist using this method, so the hole sizes are larger.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICSmoothedEdged
    Name the output image:DICSmoothedEdgedEnhanced
    Select the operation:Enhance
    Feature size:10
    Feature type:Dark holes
    Range of hole sizes:15,75
    Smoothing scale:2.0
    Shear angle:0
    Decay:0.95
    Enhancement method:Line structures

ApplyThreshold:[module_num:5|svn_version:\'6746\'|variable_revision_number:6|show_window:False|notes:\x5B\'Same idea as the previous ApplyThreshold module. A Otsu with two classes are used instead because the number of artifacts outside of actual cells is reduced.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICSmoothedEdgedEnhanced
    Name the output image:DICSmoothedEdgedEnhancedBinary
    Select the output image type:Binary (black and white)
    Set pixels below or above the threshold to zero?:Below threshold
    Subtract the threshold value from the remaining pixel intensities?:No
    Number of pixels by which to expand the thresholding around those excluded bright pixels:0.0
    Select the thresholding method:Otsu Global
    Manual threshold:0.01
    Lower and upper bounds on threshold:0.001,0.01
    Threshold correction factor:1.0
    Approximate fraction of image covered by objects?:0.01
    Select the input objects:None
    Two-class or three-class thresholding?:Two classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Foreground
    Select the measurement to threshold with:None

EnhanceOrSuppressFeatures:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:4|show_window:False|notes:\x5B"This module finds \'dark holes\' in the smoothed DIC images, making them bright and setting all other pixels to 0. These \'dark holes\' are depressed areas fully contained within a boundary of lighter pixels. The reason the \'range of hole sizes\' is relatively small and narrow is because cells have internal bright spots which are seen as a boundary of a hole."\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICSmoothed
    Name the output image:DICSmoothedEnhanced
    Select the operation:Enhance
    Feature size:10
    Feature type:Dark holes
    Range of hole sizes:10,20
    Smoothing scale:2.0
    Shear angle:0
    Decay:0.95
    Enhancement method:Line structures

ApplyThreshold:[module_num:7|svn_version:\'6746\'|variable_revision_number:6|show_window:False|notes:\x5B"The dark hole image will have bright areas which mostly match yeast cells (or possibly some debris), typically the cell boundry\'s shadow and some other internal shadows. These will be different brightnesses, depending on the size and brightness of the bounding bright pixels. The difference in intensity doesn\'t provide useful information for us, so we\'ll convert them all to binary, using a threshold calculated via Otsu with three classes, weighted variance mode, assigning the middle class to the background. The threshold bounds help protect the results of the algorithm from going far out of wack."\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICSmoothedEnhanced
    Name the output image:DICSmoothedEnhancedBinary
    Select the output image type:Binary (black and white)
    Set pixels below or above the threshold to zero?:Below threshold
    Subtract the threshold value from the remaining pixel intensities?:No
    Number of pixels by which to expand the thresholding around those excluded bright pixels:0.0
    Select the thresholding method:Otsu Global
    Manual threshold:0.01
    Lower and upper bounds on threshold:0.001,0.01
    Threshold correction factor:1.0
    Approximate fraction of image covered by objects?:0.01
    Select the input objects:None
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Select the measurement to threshold with:None

Smooth:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the first supplemental fluorescence image using a median filter. This helps reduce the single-pixel noise and makes the denser cellular intensity stand out.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCer
    Name the output image:MTSmCerSmoothed
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:5.0
    Edge intensity difference:0.1

Smooth:[module_num:9|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerSmoothed
    Name the output image:MTSmCerBackground
    Select smoothing method:Fit Polynomial
    Calculate artifact diameter automatically?:Yes
    Typical artifact diameter, in  pixels:16.0
    Edge intensity difference:0.1

ImageMath:[module_num:10|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Add
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:MTSmCerSmoothedLessBackground
    Image or measurement?:Image
    Select the first image:MTSmCerSmoothed
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MTSmCerBackground
    Multiply the second image by:1
    Measurement:

ApplyThreshold:[module_num:11|svn_version:\'6746\'|variable_revision_number:6|show_window:False|notes:\x5B\'Convert the supplemental fluorescence image to binary, using an empirically-determined threshold value which assigns most background pixels to 0, but assigns most cellular autofluorescence and true fluorescence to 1. This is because the information we care about from here is "cell" or "not cell".\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerSmoothed
    Name the output image:MTSmCerSmoothedThresholded
    Select the output image type:Binary (black and white)
    Set pixels below or above the threshold to zero?:Below threshold
    Subtract the threshold value from the remaining pixel intensities?:No
    Number of pixels by which to expand the thresholding around those excluded bright pixels:0.0
    Select the thresholding method:Otsu Global
    Manual threshold:0.003
    Lower and upper bounds on threshold:0.002,0.01
    Threshold correction factor:1.0
    Approximate fraction of image covered by objects?:0.01
    Select the input objects:None
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Select the measurement to threshold with:None

Morph:[module_num:12|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Even with the prior smoothing, the threshold is low enough to be impacted by noise, resulting in spurs and other odd artifacts. Opening once and then performing a majority operation helps remove remaining noise from the medium and slightly rounds the objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerSmoothedThresholded
    Name the output image:MTSmCerSmoothedThresholdedMorphed
    Select the operation to perform:open
    Number of times to repeat operation:Once
    Repetition number:1
    Scale:3
    Select the operation to perform:close
    Number of times to repeat operation:Once
    Repetition number:2
    Scale:3

Smooth:[module_num:13|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the second supplemental fluorescence image using a median filter. This helps reduce the single-pixel noise and makes the denser cellular intensity stand out.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTom
    Name the output image:NLStdTomSmoothed
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:5.0
    Edge intensity difference:0.1

ApplyThreshold:[module_num:14|svn_version:\'6746\'|variable_revision_number:6|show_window:False|notes:\x5B\'Convert the supplemental fluorescence image to binary, using an empirically-determined threshold value which assigns most background pixels to 0, but assigns most cellular autofluorescence and true fluorescence to 1. This is because the information we care about from here is "cell" or "not cell".\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomSmoothed
    Name the output image:NLStdTomSmoothedThresholded
    Select the output image type:Binary (black and white)
    Set pixels below or above the threshold to zero?:Below threshold
    Subtract the threshold value from the remaining pixel intensities?:No
    Number of pixels by which to expand the thresholding around those excluded bright pixels:0.0
    Select the thresholding method:Otsu Global
    Manual threshold:0.003
    Lower and upper bounds on threshold:0.002,0.01
    Threshold correction factor:1.0
    Approximate fraction of image covered by objects?:0.01
    Select the input objects:None
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Select the measurement to threshold with:None

Morph:[module_num:15|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Even with the prior smoothing, the threshold is low enough to be impacted by noise, resulting in spurs and other odd artifacts. Opening once and then performing a majority operation helps remove remaining noise from the medium and slightly rounds the objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomSmoothedThresholded
    Name the output image:NLStdTomSmoothedThresholdedMorphed
    Select the operation to perform:open
    Number of times to repeat operation:Once
    Repetition number:1
    Scale:3
    Select the operation to perform:majority
    Number of times to repeat operation:Once
    Repetition number:2
    Scale:3

ImageMath:[module_num:16|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Combine information from the main DIC channels and the supplemntary fluorescence. The edged-DIC-originated information  more closely aligns with the real border of the cell. However, a few cells have a weak border, which extends the signal several pixels beyond the cell walls. Little can be done about it at this stage. The DIC-originated information is generally slightly bigger than the boundary of the cell, so we weight it as half. The supplemental fluorescence-originated information is probably about the right size for the cell, but may be less regularly shaped. Some cells are found by one channel but not others, and some methods can miss some cell information. The combination of these information channels results in more robust cell-finding.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Maximum
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:DICProcessed
    Image or measurement?:Image
    Select the first image:DICSmoothedEdgedEnhancedBinary
    Multiply the first image by:1.0
    Measurement:
    Image or measurement?:Image
    Select the second image:DICSmoothedEnhancedBinary
    Multiply the second image by:0.5
    Measurement:
    Image or measurement?:Image
    Select the third image:MTSmCerSmoothedThresholdedMorphed
    Multiply the third image by:0.5
    Measurement:
    Image or measurement?:Image
    Select the fourth image:NLStdTomSmoothedThresholdedMorphed
    Multiply the fourth image by:1
    Measurement:

Smooth:[module_num:17|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'IdentifyObjects modules require a gradient to reliably detect objects. Applying a Gaussian filter achieves this.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICProcessed
    Name the output image:DICProcessedSmoothed
    Select smoothing method:Gaussian Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:5.0
    Edge intensity difference:0.1

IdentifyPrimaryObjects:[module_num:18|svn_version:\'Unknown\'|variable_revision_number:9|show_window:False|notes:\x5B"Using the previously-obtained cell information, we find the cell objects using a threshold of 0.4, since our information ranges from 0 to 1 per pixel and the body of each cell is 1 and falls off (due to Gaussian smoothing) to 0 over several pixels. Clumped objects are separated liberally using intensity and rejoined in the next module. A few very close cells won\'t have an intensity difference between them and so won\'t be separated by this method."\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICProcessedSmoothed
    Name the primary objects to be identified:CellsPreliminary
    Typical diameter of objects, in pixel units (Min,Max):25,100
    Discard objects outside the diameter range?:No
    Try to merge too small objects with nearby larger objects?:No
    Discard objects touching the border of the image?:No
    Select the thresholding method:Manual
    Threshold correction factor:1.0
    Lower and upper bounds on threshold:0.1,0.5
    Approximate fraction of image covered by objects?:0.01
    Method to distinguish clumped objects:Intensity
    Method to draw dividing lines between clumped objects:Intensity
    Size of smoothing filter:50
    Suppress local maxima that are closer than this minimum allowed distance:5
    Speed up by using lower-resolution image to find local maxima?:No
    Name the outline image:PrimaryOutlines
    Fill holes in identified objects?:Yes
    Automatically calculate size of smoothing filter?:Yes
    Automatically calculate minimum allowed distance between local maxima?:No
    Manual threshold:0.4
    Select binary image:None
    Retain outlines of the identified objects?:No
    Automatically calculate the threshold using the Otsu method?:Yes
    Enter Laplacian of Gaussian threshold:0.8
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Automatically calculate the size of objects for the Laplacian of Gaussian filter?:Yes
    Enter LoG filter diameter:25
    Handling of objects if excessive number of objects identified:Continue
    Maximum number of objects:500
    Select the measurement to threshold with:None
    Method to calculate adaptive window size:Image size
    Size of adaptive window:10

UnifyObjectsByShape:[module_num:19|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:CellsPreliminary
    Name the new objects:CellsPreliminaryUnified
    Retain outlines of the relabeled objects?:No
    Name the outlines:RelabeledCellOutlines
    Window size:10
    Threshold:0.5

MeasureObjectSizeShape:[module_num:20|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to measure:CellsPreliminaryUnified
    Calculate the Zernike features?:Yes

FilterObjects:[module_num:21|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B"Filter out \'cells\' which are too small to be cells."\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:Cells
    Select the object to filter:CellsPreliminaryUnified
    Filter using classifier rules or measurements?:Measurements
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder\x7CNone
    Rules file name:rules.txt
    Class number:1
    Measurement count:1
    Additional object count:0
    Select the measurement to filter by:AreaShape_Area
    Filter using a minimum measurement value?:Yes
    Minimum value:150
    Filter using a maximum measurement value?:No
    Maximum value:1

FilterObjects:[module_num:22|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:CellsWhole
    Select the object to filter:Cells
    Filter using classifier rules or measurements?:Border
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder\x7CNone
    Rules file name:rules.txt
    Class number:1
    Measurement count:1
    Additional object count:0
    Select the measurement to filter by:AreaShape_Area
    Filter using a minimum measurement value?:Yes
    Minimum value:0
    Filter using a maximum measurement value?:Yes
    Maximum value:1

MeasureObjectSizeShape:[module_num:23|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to measure:CellsWhole
    Calculate the Zernike features?:Yes

SaveImages:[module_num:24|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the filtered cell objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Objects
    Select the image to save:None
    Select the objects to save:CellsWhole
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:DIC (Corrected)
    Enter single file name:Cells Preliminary (\\\\g<Strain> - \\\\g<Colony> - \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:png
    Output file location:Default Input Folder sub-folder\x7CObjects
    Image bit depth:8
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

ExportToSpreadsheet:[module_num:25|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select or enter the column delimiter:Comma (",")
    Prepend the output file name to the data file names?:Yes
    Add image metadata columns to your object data file?:Yes
    Limit output to a size that is allowed in Excel?:No
    Select the columns of measurements to export?:No
    Calculate the per-image mean values for object measurements?:No
    Calculate the per-image median values for object measurements?:No
    Calculate the per-image standard deviation values for object measurements?:No
    Output file location:Default Output Folder\x7CNone
    Create a GenePattern GCT file?:No
    Select source of sample row name:Metadata
    Select the image to use as the identifier:None
    Select the metadata to use as the identifier:None
    Export all measurements, using default file names?:No
    Press button to select measurements to export:
    Data to export:Image
    Combine these object measurements with those of the previous object?:No
    File name:Image Data for Bad Cell Filtering Analysis.csv
    Use the object name for the file name?:No
    Data to export:CellsWhole
    Combine these object measurements with those of the previous object?:No
    File name:Cell Object Shape and Size Data for Bad Cell Filtering Analysis.csv
    Use the object name for the file name?:No
