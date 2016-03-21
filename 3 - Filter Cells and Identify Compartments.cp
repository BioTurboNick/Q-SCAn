CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130722225601

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the fluorescence channels used for compartment identification.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:Do not use
    Analyze all subfolders within the selected folder?:All
    Input image file location:Default Input Folder sub-folder\x7CFully Corrected Images
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:No
    Specify metadata fields to group by:Colony,Field,Strain
    Select subfolders to analyze:
    Image count:2
    Text that these images have in common (case-sensitive):Ch3-T1
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*(?P<Strain>.*) - Field (?P<Field>S*).lsm
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
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch2-T3
    Position of this image in each group:2
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*(?P<Strain>.*) - Field (?P<Field>S*).lsm
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

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the cell objects.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:Do not use
    Analyze all subfolders within the selected folder?:None
    Input image file location:Default Input Folder sub-folder\x7CObjects
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:No
    Specify metadata fields to group by:
    Select subfolders to analyze:
    Image count:1
    Text that these images have in common (case-sensitive):Cells (
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*(?P<Strain>.*) - Field (?P<Field>S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:CellsImage
    Name this loaded object:Cells
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No

LoadData:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\'Q-SCAn Program\x3A Load the computed normalization values.\', \'If not using the program, you will should remove this module and manually set the values in RescaleIntensity based on the data output by the previous pipeline.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Input data file location:Default Input Folder sub-folder\x7COutput Data
    Name of the file:Within-Cell Image Intensities for Normalization.csv
    Load images based on this data?:No
    Base image location:Default Input Folder\x7CNone
    Process just a range of rows?:No
    Rows to process:1,100000
    Group images by metadata?:No
    Select metadata fields for grouping:
    Rescale intensities?:Yes

RescaleIntensity:[module_num:4|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Normalize the image so that the mean of the intensities within cells for the fluorophor = 0.01. This value is determined by dividing the cross-dataset intensity sum and area sum to find the mean cellular intensity for the marker. This number must be multiplied by 100 and entered here.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTom
    Name the output image:NLStdTomNormalized
    Select rescaling method:Divide each image by a previously calculated value
    How do you want to calculate the minimum intensity?:Custom
    How do you want to calculate the maximum intensity?:Custom
    Enter the lower limit for the intensity range for the input image:0
    Enter the upper limit for the intensity range for the input image:1
    Enter the intensity range for the input image:0.000000,1.000000
    Enter the desired intensity range for the final, rescaled image:0.000000,1.000000
    Select method for rescaling pixels below the lower limit:Mask pixels
    Enter custom value for pixels below lower limit:0
    Select method for rescaling pixels above the upper limit:Mask pixels
    Enter custom value for pixels below upper limit:0
    Select image to match in maximum intensity:None
    Enter the divisor:1.154495982
    Select the measurement to use as a divisor:DatasetAverageIntensity_NLStdTomLessNoise

RescaleIntensity:[module_num:5|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Normalize the image so that the mean of the intensities within cells for the fluorophor = 0.01. This value is determined by dividing the cross-dataset intensity sum and area sum to find the mean cellular intensity for the marker. This number must be multiplied by 100 and entered here.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCer
    Name the output image:MTSmCerNormalized
    Select rescaling method:Divide each image by a previously calculated value
    How do you want to calculate the minimum intensity?:Custom
    How do you want to calculate the maximum intensity?:Custom
    Enter the lower limit for the intensity range for the input image:0
    Enter the upper limit for the intensity range for the input image:1
    Enter the intensity range for the input image:0.000000,1.000000
    Enter the desired intensity range for the final, rescaled image:0.000000,1.000000
    Select method for rescaling pixels below the lower limit:Mask pixels
    Enter custom value for pixels below lower limit:0
    Select method for rescaling pixels above the upper limit:Mask pixels
    Enter custom value for pixels below upper limit:0
    Select image to match in maximum intensity:None
    Enter the divisor:0.747276876
    Select the measurement to use as a divisor:DatasetAverageIntensity_MTSmCerLessNoise

MeasureObjectIntensity:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Hidden:2
    Select an image to measure:NLStdTomNormalized
    Select an image to measure:MTSmCerNormalized
    Select objects to measure:Cells

FilterObjects:[module_num:7|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\'Remove cells with very low expression of the compartment-defining fluorescence channel. Based on normalized images.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:CellsFilteredByLowNLStdTom
    Select the object to filter:Cells
    Filter using classifier rules or measurements?:Rules
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder sub-folder\x7C..
    Rules file name:LowNLStdTomFluorescenceFilterRules.txt
    Class number:1
    Measurement count:1
    Additional object count:0
    Select the measurement to filter by:AreaShape_Area
    Filter using a minimum measurement value?:Yes
    Minimum value:0
    Filter using a maximum measurement value?:Yes
    Maximum value:1

FilterObjects:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\'Remove cells with very low expression of the compartment-defining fluorescence channel.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:CellsFilteredByLowMTSmCer
    Select the object to filter:Cells
    Filter using classifier rules or measurements?:Rules
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder sub-folder\x7C..
    Rules file name:LowMTSmCerFluorescenceFilterRules.txt
    Class number:1
    Measurement count:1
    Additional object count:0
    Select the measurement to filter by:AreaShape_Area
    Filter using a minimum measurement value?:Yes
    Minimum value:0
    Filter using a maximum measurement value?:Yes
    Maximum value:1

MaskObjects:[module_num:9|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Combine the filitering results to retain only those cells with appreciable expression of the compartment-defining markers.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to be masked:CellsFilteredByLowNLStdTom
    Name the masked objects:CellsFilteredByLowMarkerIntensity
    Mask using a region defined by other objects or by binary image?:Objects
    Select the masking object(s):CellsFilteredByLowMTSmCer
    Select the masking image:None
    Handling of objects that are partially masked:Keep
    Fraction of object that must overlap:0.5
    Numbering of resulting objects:Renumber
    Retain outlines of the resulting objects?:No
    Name the outline image:MaskedOutlines
    Invert the mask?:No

Smooth:[module_num:10|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image to remove the effect of noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomNormalized
    Name the output image:NLStdTomNormalizedSmoothed
    Select smoothing method:Gaussian Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2.0
    Edge intensity difference:0.1

MaskImage:[module_num:11|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Mask the image by the cell objects to allow per-object thresholding.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomNormalizedSmoothed
    Name the output image:NLStdTomNormalizedSmoothedMasked
    Use objects or an image as a mask?:Objects
    Select object for mask:CellsFilteredByLowMarkerIntensity
    Select image for mask:None
    Invert the mask?:No

IdentifyPrimaryObjects:[module_num:12|svn_version:\'Unknown\'|variable_revision_number:9|show_window:False|notes:\x5B\'Find nuclei objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomNormalizedSmoothedMasked
    Name the primary objects to be identified:NucleiPreliminary
    Typical diameter of objects, in pixel units (Min,Max):5,50
    Discard objects outside the diameter range?:Yes
    Try to merge too small objects with nearby larger objects?:No
    Discard objects touching the border of the image?:No
    Select the thresholding method:Otsu PerObject
    Threshold correction factor:1
    Lower and upper bounds on threshold:0.000000,1.000000
    Approximate fraction of image covered by objects?:0.01
    Method to distinguish clumped objects:None
    Method to draw dividing lines between clumped objects:Intensity
    Size of smoothing filter:10
    Suppress local maxima that are closer than this minimum allowed distance:7
    Speed up by using lower-resolution image to find local maxima?:Yes
    Name the outline image:PrimaryOutlines
    Fill holes in identified objects?:No
    Automatically calculate size of smoothing filter?:Yes
    Automatically calculate minimum allowed distance between local maxima?:Yes
    Manual threshold:0.0
    Select binary image:None
    Retain outlines of the identified objects?:No
    Automatically calculate the threshold using the Otsu method?:Yes
    Enter Laplacian of Gaussian threshold:0.5
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Automatically calculate the size of objects for the Laplacian of Gaussian filter?:Yes
    Enter LoG filter diameter:5
    Handling of objects if excessive number of objects identified:Continue
    Maximum number of objects:500
    Select the measurement to threshold with:None
    Method to calculate adaptive window size:Image size
    Size of adaptive window:10

RelateObjects:[module_num:13|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Relate the nuclei objects to the parent cells.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input child objects:NucleiPreliminary
    Select the input parent objects:CellsFilteredByLowMarkerIntensity
    Calculate distances?:None
    Calculate per-parent means for all child measurements?:No
    Calculate distances to other parents?:No
    Parent name:None

ReassignObjectNumbers:[module_num:14|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Renumber the nuclei objects to match their parents. Has the effect of merging separate objects within the same parent.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:NucleiPreliminary
    Name the new objects:NucleiPreliminaryRelated
    Operation to perform:Unify
    Maximum distance within which to unify objects:0
    Unify using a grayscale image?:No
    Select the grayscale image to guide unification:None
    Minimum intensity fraction:0.9
    Method to find object intensity:Closest point
    Retain outlines of the relabeled objects?:No
    Name the outlines:RelabeledNucleiOutlines
    Unification to perform:Per-parent
    Select the parent object:CellsFilteredByLowMarkerIntensity

Smooth:[module_num:15|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image to remove the effect of noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerNormalized
    Name the output image:MTSmCerNormalizedSmoothed
    Select smoothing method:Gaussian Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2.0
    Edge intensity difference:0.1

MaskImage:[module_num:16|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Mask the image by the cell objects to allow per-object thresholding.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerNormalizedSmoothed
    Name the output image:MTSmCerNormalizedSmoothedMasked
    Use objects or an image as a mask?:Objects
    Select object for mask:CellsFilteredByLowMarkerIntensity
    Select image for mask:None
    Invert the mask?:No

IdentifyPrimaryObjects:[module_num:17|svn_version:\'Unknown\'|variable_revision_number:9|show_window:False|notes:\x5B\'Find the mitochondria.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerNormalizedSmoothedMasked
    Name the primary objects to be identified:MitochondriaPreliminary
    Typical diameter of objects, in pixel units (Min,Max):2,50
    Discard objects outside the diameter range?:Yes
    Try to merge too small objects with nearby larger objects?:No
    Discard objects touching the border of the image?:No
    Select the thresholding method:RobustBackground PerObject
    Threshold correction factor:0.8
    Lower and upper bounds on threshold:0.000000,1.000000
    Approximate fraction of image covered by objects?:0.01
    Method to distinguish clumped objects:None
    Method to draw dividing lines between clumped objects:Intensity
    Size of smoothing filter:10
    Suppress local maxima that are closer than this minimum allowed distance:7
    Speed up by using lower-resolution image to find local maxima?:Yes
    Name the outline image:PrimaryOutlines
    Fill holes in identified objects?:No
    Automatically calculate size of smoothing filter?:Yes
    Automatically calculate minimum allowed distance between local maxima?:Yes
    Manual threshold:0.0
    Select binary image:None
    Retain outlines of the identified objects?:No
    Automatically calculate the threshold using the Otsu method?:Yes
    Enter Laplacian of Gaussian threshold:0.5
    Two-class or three-class thresholding?:Three classes
    Minimize the weighted variance or the entropy?:Weighted variance
    Assign pixels in the middle intensity class to the foreground or the background?:Background
    Automatically calculate the size of objects for the Laplacian of Gaussian filter?:Yes
    Enter LoG filter diameter:5
    Handling of objects if excessive number of objects identified:Continue
    Maximum number of objects:500
    Select the measurement to threshold with:None
    Method to calculate adaptive window size:Image size
    Size of adaptive window:10

RelateObjects:[module_num:18|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Relate the mitochondrial objects to the parent cells.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input child objects:MitochondriaPreliminary
    Select the input parent objects:CellsFilteredByLowMarkerIntensity
    Calculate distances?:None
    Calculate per-parent means for all child measurements?:No
    Calculate distances to other parents?:No
    Parent name:None

ReassignObjectNumbers:[module_num:19|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Renumber the nuclei objects to match their parents. Has the effect of merging separate objects within the same parent.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:MitochondriaPreliminary
    Name the new objects:MitochondriaPreliminaryRelated
    Operation to perform:Unify
    Maximum distance within which to unify objects:0
    Unify using a grayscale image?:No
    Select the grayscale image to guide unification:None
    Minimum intensity fraction:0.9
    Method to find object intensity:Closest point
    Retain outlines of the relabeled objects?:No
    Name the outlines:RelabeledNucleiOutlines
    Unification to perform:Per-parent
    Select the parent object:CellsFilteredByLowMarkerIntensity

MeasureObjectSizeShape:[module_num:20|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to measure:CellsFilteredByLowMarkerIntensity
    Select objects to measure:NucleiPreliminaryRelated
    Select objects to measure:MitochondriaPreliminaryRelated
    Calculate the Zernike features?:No

CalculateMath:[module_num:21|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Calculate the fractional area of each cell which is taken up by the nucleus.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:FractionNuclear
    Operation:Divide
    Select the numerator measurement type:Object
    Select the numerator objects:NucleiPreliminaryRelated
    Select the numerator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the denominator measurement type:Object
    Select the denominator objects:CellsFilteredByLowMarkerIntensity
    Select the denominator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:22|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Calculate the fractional area of each cell which is taken up by the mitochondria.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:FractionMitochondria
    Operation:Divide
    Select the numerator measurement type:Object
    Select the numerator objects:MitochondriaPreliminaryRelated
    Select the numerator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the denominator measurement type:Object
    Select the denominator objects:CellsFilteredByLowMarkerIntensity
    Select the denominator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

FilterObjects:[module_num:23|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\'Remove cells which have overly large nuclei (>25% area) or mitochondria (>50% area). When objects take up this much of the cell, they tend to be due to a cell with badly-localized marker proteins.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:CellsFilteredByMaximumCompartmentSize
    Select the object to filter:CellsFilteredByLowMarkerIntensity
    Filter using classifier rules or measurements?:Measurements
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder\x7CNone
    Rules file name:rules.txt
    Class number:1
    Measurement count:2
    Additional object count:2
    Select the measurement to filter by:Math_FractionNuclear
    Filter using a minimum measurement value?:No
    Minimum value:1.0
    Filter using a maximum measurement value?:Yes
    Maximum value:0.25
    Select the measurement to filter by:Math_FractionMitochondria
    Filter using a minimum measurement value?:No
    Minimum value:1.0
    Filter using a maximum measurement value?:Yes
    Maximum value:0.5
    Select additional object to relabel:NucleiPreliminaryRelated
    Name the relabeled objects:NucleiFilteredByMaximumCompartmentSize
    Retain outlines of relabeled objects?:No
    Name the outline image:OutlinesFilteredGreen
    Select additional object to relabel:MitochondriaPreliminaryRelated
    Name the relabeled objects:MitochondriaFilteredByMaximumCompartmentSize
    Retain outlines of relabeled objects?:No
    Name the outline image:OutlinesFilteredGreen

ExpandOrShrinkObjects:[module_num:24|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Expand the nuclei object by 1 pixel.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:NucleiFilteredByMaximumCompartmentSize
    Name the output objects:NucleiExpanded
    Select the operation:Expand objects by a specified number of pixels
    Number of pixels by which to expand or shrink:1
    Fill holes in objects so that all objects shrink to a single point?:No
    Retain the outlines of the identified objects for use later in the pipeline (for example, in SaveImages)?:No
    Name the outline image:ShrunkenNucleiOutlines

ExpandOrShrinkObjects:[module_num:25|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Expand the mitochondria object by 1 pixel.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:MitochondriaFilteredByMaximumCompartmentSize
    Name the output objects:MitochondriaExpanded
    Select the operation:Expand objects by a specified number of pixels
    Number of pixels by which to expand or shrink:1
    Fill holes in objects so that all objects shrink to a single point?:No
    Retain the outlines of the identified objects for use later in the pipeline (for example, in SaveImages)?:No
    Name the outline image:ShrunkenNucleiOutlines

MaskObjects:[module_num:26|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Remove those nuclear pixels that are also part of the expanded mitochondria in order to obtain the portion of the cell which is purely nuclear.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to be masked:NucleiFilteredByMaximumCompartmentSize
    Name the masked objects:PureNuclei
    Mask using a region defined by other objects or by binary image?:Objects
    Select the masking object(s):MitochondriaExpanded
    Select the masking image:None
    Handling of objects that are partially masked:Keep overlapping region
    Fraction of object that must overlap:0.5
    Numbering of resulting objects:Retain
    Retain outlines of the resulting objects?:No
    Name the outline image:MaskedOutlines
    Invert the mask?:Yes

MaskObjects:[module_num:27|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Remove those mitochondrial pixels that are also part of the expanded nucleus in order to obtain the portion of the cell which is purely mitochondrial.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to be masked:MitochondriaFilteredByMaximumCompartmentSize
    Name the masked objects:PureMitochondria
    Mask using a region defined by other objects or by binary image?:Objects
    Select the masking object(s):NucleiExpanded
    Select the masking image:None
    Handling of objects that are partially masked:Keep overlapping region
    Fraction of object that must overlap:0.5
    Numbering of resulting objects:Retain
    Retain outlines of the resulting objects?:No
    Name the outline image:MaskedOutlines
    Invert the mask?:Yes

RelateObjects:[module_num:28|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Relate the pure nuclei to the parent cells. Note\x3A Must be placed after CalculateMath.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input child objects:PureNuclei
    Select the input parent objects:CellsFilteredByMaximumCompartmentSize
    Calculate distances?:None
    Calculate per-parent means for all child measurements?:No
    Calculate distances to other parents?:No
    Parent name:None

RelateObjects:[module_num:29|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Relate the pure mitochondria to the parent cells. Note\x3A Must be placed after CalculateMath.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input child objects:PureMitochondria
    Select the input parent objects:CellsFilteredByMaximumCompartmentSize
    Calculate distances?:None
    Calculate per-parent means for all child measurements?:No
    Calculate distances to other parents?:No
    Parent name:None

ReassignObjectNumbers:[module_num:30|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:PureNuclei
    Name the new objects:RelabeledPureNuclei
    Operation to perform:Unify
    Maximum distance within which to unify objects:0
    Unify using a grayscale image?:No
    Select the grayscale image to guide unification:None
    Minimum intensity fraction:0.9
    Method to find object intensity:Closest point
    Retain outlines of the relabeled objects?:No
    Name the outlines:RelabeledNucleiOutlines
    Unification to perform:Per-parent
    Select the parent object:CellsFilteredByMaximumCompartmentSize

ReassignObjectNumbers:[module_num:31|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:PureMitochondria
    Name the new objects:RelabeledPureMitochondria
    Operation to perform:Unify
    Maximum distance within which to unify objects:0
    Unify using a grayscale image?:No
    Select the grayscale image to guide unification:None
    Minimum intensity fraction:0.9
    Method to find object intensity:Closest point
    Retain outlines of the relabeled objects?:No
    Name the outlines:RelabeledNucleiOutlines
    Unification to perform:Per-parent
    Select the parent object:CellsFilteredByMaximumCompartmentSize

MeasureObjectSizeShape:[module_num:32|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select objects to measure:CellsFilteredByMaximumCompartmentSize
    Select objects to measure:RelabeledPureNuclei
    Select objects to measure:RelabeledPureMitochondria
    Calculate the Zernike features?:No

CalculateMath:[module_num:33|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Calculate the fractional area of each cell which is taken up by pure nucleus.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:FractionPureNuclear
    Operation:Divide
    Select the numerator measurement type:Object
    Select the numerator objects:RelabeledPureNuclei
    Select the numerator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the denominator measurement type:Object
    Select the denominator objects:CellsFilteredByMaximumCompartmentSize
    Select the denominator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:34|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Calculate the fractional area of each cell which is taken up by pure mitochondria.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:FractionPureMitochondria
    Operation:Divide
    Select the numerator measurement type:Object
    Select the numerator objects:RelabeledPureMitochondria
    Select the numerator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the denominator measurement type:Object
    Select the denominator objects:CellsFilteredByMaximumCompartmentSize
    Select the denominator measurement:AreaShape_Area
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

FilterObjects:[module_num:35|svn_version:\'Unknown\'|variable_revision_number:6|show_window:False|notes:\x5B\'Remove those cells containing less than 1% of their area as pure nuclei or pure mitochondria objects. This is to ensure that a large enough pixels remain for a robust measure.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output objects:CellsFilteredByMinimumCompartmentSize
    Select the object to filter:CellsFilteredByMaximumCompartmentSize
    Filter using classifier rules or measurements?:Measurements
    Select the filtering method:Limits
    Select the objects that contain the filtered objects:None
    Retain outlines of the identified objects?:No
    Name the outline image:FilteredObjects
    Rules file location:Default Input Folder\x7CNone
    Rules file name:rules.txt
    Class number:1
    Measurement count:4
    Additional object count:2
    Select the measurement to filter by:Math_FractionPureNuclear
    Filter using a minimum measurement value?:Yes
    Minimum value:0.01
    Filter using a maximum measurement value?:No
    Maximum value:0.25
    Select the measurement to filter by:Math_FractionPureMitochondria
    Filter using a minimum measurement value?:Yes
    Minimum value:0.01
    Filter using a maximum measurement value?:No
    Maximum value:1
    Select the measurement to filter by:Children_PureNuclei_Count
    Filter using a minimum measurement value?:Yes
    Minimum value:1
    Filter using a maximum measurement value?:No
    Maximum value:1
    Select the measurement to filter by:Children_PureMitochondria_Count
    Filter using a minimum measurement value?:Yes
    Minimum value:1
    Filter using a maximum measurement value?:No
    Maximum value:1
    Select additional object to relabel:PureNuclei
    Name the relabeled objects:PureNucleiFilteredByMinimumCompartmentSize
    Retain outlines of relabeled objects?:No
    Name the outline image:OutlinesFilteredGreen
    Select additional object to relabel:PureMitochondria
    Name the relabeled objects:PureMitochondriaFilteredByMinimumCompartmentSize
    Retain outlines of relabeled objects?:No
    Name the outline image:OutlinesFilteredGreen

IdentifyTertiaryObjects:[module_num:36|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the larger identified objects:CellsFilteredByMinimumCompartmentSize
    Select the smaller identified objects:NucleiExpanded
    Name the tertiary objects to be identified:PreCytoplasm
    Name the outline image:CytoplasmOutlines
    Retain outlines of the tertiary objects?:No
    Shrink primary object?:No

IdentifyTertiaryObjects:[module_num:37|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the larger identified objects:PreCytoplasm
    Select the smaller identified objects:MitochondriaExpanded
    Name the tertiary objects to be identified:Cytoplasm
    Name the outline image:CytoplasmOutlines
    Retain outlines of the tertiary objects?:No
    Shrink primary object?:No

SaveImages:[module_num:38|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the final, filtered cells object.\', "Q-SCAn Program\x3A The file name suffix wiithin parentheses will be overridden unless the manual setting is checked. The prefix can be safely changed, but don\'t use parentheses"\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Objects
    Select the image to save:None
    Select the objects to save:CellsFilteredByMinimumCompartmentSize
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Cells Filtered (\\\\g<Strain> - \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:png
    Output file location:Default Output Folder sub-folder\x7CObjects
    Image bit depth:8
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:39|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the pure nuclei object.\', "Q-SCAn Program\x3A The file name suffix wiithin parentheses will be overridden unless the manual setting is checked. The prefix can be safely changed, but don\'t use parentheses"\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Objects
    Select the image to save:None
    Select the objects to save:PureNucleiFilteredByMinimumCompartmentSize
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Pure Nuclei (\\\\g<Strain> - \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:png
    Output file location:Default Output Folder sub-folder\x7CObjects
    Image bit depth:8
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:40|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the pure mitochondria object.\', "Q-SCAn Program\x3A The file name suffix wiithin parentheses will be overridden unless the manual setting is checked. The prefix can be safely changed, but don\'t use parentheses"\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Objects
    Select the image to save:None
    Select the objects to save:PureMitochondriaFilteredByMinimumCompartmentSize
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Pure Mitochondria (\\\\g<Strain> - \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:png
    Output file location:Default Output Folder sub-folder\x7CObjects
    Image bit depth:8
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:41|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the cytosol object.\', "Q-SCAn Program\x3A The file name suffix wiithin parentheses will be overridden unless the manual setting is checked. The prefix can be safely changed, but don\'t use parentheses"\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Objects
    Select the image to save:None
    Select the objects to save:Cytoplasm
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Cytoplasm (\\\\g<Strain> - \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:png
    Output file location:Default Output Folder sub-folder\x7CObjects
    Image bit depth:8
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

ExportToSpreadsheet:[module_num:42|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Export the number of whole cells identified (Cells), the number left after removing low marker-expressing cells (CellsFiltered), and the number left after that and those with too small or too large compartments (CellsFiltered4).\', \'Q-SCAn Program\x3A The exported metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select or enter the column delimiter:Comma (",")
    Prepend the output file name to the data file names?:Yes
    Add image metadata columns to your object data file?:Yes
    Limit output to a size that is allowed in Excel?:No
    Select the columns of measurements to export?:Yes
    Calculate the per-image mean values for object measurements?:No
    Calculate the per-image median values for object measurements?:No
    Calculate the per-image standard deviation values for object measurements?:No
    Output file location:Default Output Folder sub-folder\x7COutput Data
    Create a GenePattern GCT file?:No
    Select source of sample row name:Metadata
    Select the image to use as the identifier:None
    Select the metadata to use as the identifier:None
    Export all measurements, using default file names?:No
    Press button to select measurements to export:Image\x7CCount_Cells,Image\x7CCount_CellsFilteredByMaximumCompartmentSize,Image\x7CCount_CellsFilteredByLowMarkerIntensity,Image\x7CCount_CellsFilteredByMinimumCompartmentSize,Image\x7CMetadata_Strain,Image\x7CMetadata_Field
    Data to export:Image
    Combine these object measurements with those of the previous object?:No
    File name:Cell Filtering Data.csv
    Use the object name for the file name?:No
