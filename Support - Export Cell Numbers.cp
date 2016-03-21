CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130109183003

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load cell, nuclei, mitochondria, and cytosol objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Text that these images have in common (case-sensitive):Cells Filtered (
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Condition>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:Yeast Cell Objects
    Name this loaded object:CellsFiltered
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Cells (
    Position of this image in each group:2
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Condition>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:Actin
    Name this loaded object:Cells
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:Yes

ConvertObjectsToImage:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:Cells
    Name the output image:CellsImage
    Select the color type:Grayscale
    Select the colormap:Default

ConvertObjectsToImage:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input objects:CellsFiltered
    Name the output image:CellsFilteredImage
    Select the color type:Grayscale
    Select the colormap:Default

DisplayDataOnImage:[module_num:4|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Display object or image measurements?:Object
    Select the input objects:Cells
    Measurement to display:Number_Object_Number
    Select the image on which to display the measurements:CellsImage
    Text color:red
    Name the output image that has the measurements displayed:CellsNumbered
    Font size (points):16
    Number of decimals:0
    Image elements to save:Image
    Annotation offset (in pixels):0

DisplayDataOnImage:[module_num:5|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Display object or image measurements?:Object
    Select the input objects:CellsFiltered
    Measurement to display:Number_Object_Number
    Select the image on which to display the measurements:CellsFilteredImage
    Text color:red
    Name the output image that has the measurements displayed:CellsFilteredNumbered
    Font size (points):16
    Number of decimals:0
    Image elements to save:Image
    Annotation offset (in pixels):0

SaveImages:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:CellsNumbered
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Cells (\\\\g<Strain> \\\\g<Condition> \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:jpeg
    Output file location:Default Output Folder sub-folder\x7Ctest
    Image bit depth:8
    Overwrite existing files without warning?:No
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:7|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:CellsFilteredNumbered
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:Single name
    Select image name for file prefix:None
    Enter single file name:Cells Filtered (\\\\g<Strain> \\\\g<Condition> \\\\g<Field>)
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name:
    Select file format to use:jpeg
    Output file location:Default Output Folder sub-folder\x7Ctest
    Image bit depth:8
    Overwrite existing files without warning?:No
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No
