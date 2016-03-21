CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130614030205

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the fluorescence channels used to define the compartments.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Position of this image in each group:3
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

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the cell and background objects.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:Median
    Analyze all subfolders within the selected folder?:All
    Input image file location:Default Input Folder sub-folder\x7CObjects
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:No
    Specify metadata fields to group by:
    Select subfolders to analyze:
    Image count:2
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
    Text that these images have in common (case-sensitive):Background (
    Position of this image in each group:2
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*(?P<Strain>.*) - Field (?P<Field>S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:BackgroundImage
    Name this loaded object:Background
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No

MeasureImageIntensity:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Measure the intensity of the background of each image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the image to measure:NLStdTom
    Measure the intensity only from areas enclosed by objects?:Yes
    Select the input objects:Background
    Select the image to measure:MTSmCer
    Measure the intensity only from areas enclosed by objects?:Yes
    Select the input objects:Background

ImageMath:[module_num:4|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Subtract 5 times the mean noise level from the first fluorescence image. This will make compartment-finding more robust.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:NLStdTomLessNoise
    Image or measurement?:Image
    Select the first image:NLStdTom
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Measurement
    Select the second image:NLStdTom
    Multiply the second image by:5.0
    Measurement:Intensity_MeanIntensity_NLStdTom_Background

ImageMath:[module_num:5|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Subtract 5 times the mean noise level from the second fluorescence image. This will make compartment-finding more robust.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:MTSmCerLessNoise
    Image or measurement?:Image
    Select the first image:MTSmCer
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Measurement
    Select the second image:NLStdTom
    Multiply the second image by:5.0
    Measurement:Intensity_MeanIntensity_MTSmCer_Background

MeasureImageIntensity:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Measure the image intensity within the cell objects after background subtraction.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the image to measure:NLStdTomLessNoise
    Measure the intensity only from areas enclosed by objects?:Yes
    Select the input objects:Cells
    Select the image to measure:MTSmCerLessNoise
    Measure the intensity only from areas enclosed by objects?:Yes
    Select the input objects:Cells

SaveImages:[module_num:7|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected images.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:NLStdTomLessNoise
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:NLStdTom
    Enter single file name:
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CFully Corrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected images.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:MTSmCerLessNoise
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:MTSmCer
    Enter single file name:
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CFully Corrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

ExportToSpreadsheet:[module_num:9|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Export the image intensity measurements. These values will be used to compute a cross-dataset mean intensity to normalize the intensities.\', "Q-SCAn Program\x3A The exported metadata fields will be automatically set unless the manual setting is checked. Please don\'t change the file name, unless you turn off completion detection."\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select or enter the column delimiter:Comma (",")
    Prepend the output file name to the data file names?:Yes
    Add image metadata columns to your object data file?:No
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
    Press button to select measurements to export:Image\x7CIntensity_TotalIntensity_MTSmCerLessNoise_Cells,Image\x7CIntensity_TotalIntensity_NLStdTomLessNoise_Cells,Image\x7CIntensity_TotalArea_MTSmCerLessNoise_Cells,Image\x7CIntensity_TotalArea_NLStdTomLessNoise_Cells,Image\x7CMetadata_Strain,Image\x7CMetadata_Field
    Data to export:Image
    Combine these object measurements with those of the previous object?:No
    File name:Within-Cell Image Intensities for Normalization.csv
    Use the object name for the file name?:No
