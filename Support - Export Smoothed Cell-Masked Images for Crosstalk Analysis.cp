CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130716184944

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5Bu\'Load each channel of the image to be analyzed this round.\'\x5D|batch_state:array(\'\', \n      dtype=\'\x7CS1\')]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:
    Analyze all subfolders within the selected folder?:All
    Input image file location:Default Input Folder sub-folder\x7CCorrected Images
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:No
    Specify metadata fields to group by:
    Select subfolders to analyze:
    Image count:3
    Text that these images have in common (case-sensitive):Ch3-T1
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:\\\\((?P<Strain>.*) (?P<Condition>\\\\S*) (?P<Field>\\\\S*)\\\\)
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
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
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
    Text that these images have in common (case-sensitive):Ch2-T2
    Position of this image in each group:3
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:GFP
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:Yes

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the filtered cell objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Image count:1
    Text that these images have in common (case-sensitive):Cells (
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:Yeast Cell Objects
    Name this loaded object:Cells
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No

Smooth:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTom
    Name the output image:FilteredNLStdTom
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

Smooth:[module_num:4|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCer
    Name the output image:FilteredMTSmCer
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

Smooth:[module_num:5|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:GFP
    Name the output image:FilteredGFP
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

MaskImage:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Mask the image to only get the cell pixels.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:FilteredNLStdTom
    Name the output image:MaskedNLStdTom
    Use objects or an image as a mask?:Objects
    Select object for mask:Cells
    Select image for mask:None
    Invert the mask?:No

MaskImage:[module_num:7|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Mask the image to only get the cell pixels.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:FilteredMTSmCer
    Name the output image:MaskedMTSmCer
    Use objects or an image as a mask?:Objects
    Select object for mask:Cells
    Select image for mask:None
    Invert the mask?:No

MaskImage:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Mask the image to only get the cell pixels.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:FilteredGFP
    Name the output image:MaskedGFP
    Use objects or an image as a mask?:Objects
    Select object for mask:Cells
    Select image for mask:None
    Invert the mask?:No

SaveImages:[module_num:9|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the images out for ImageJ to export the pixel data.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:MaskedNLStdTom
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:NLStdTom
    Enter single file name:OrigBlue
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name: (\\\\g<Strain> \\\\g<Colony> \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CMasked Smoothed Images for Crosstalk Analysis
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:10|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the images out for ImageJ to export the pixel data.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:MaskedMTSmCer
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:MTSmCer
    Enter single file name:OrigBlue
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name: (\\\\g<Strain> \\\\g<Colony> \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CMasked Smoothed Images for Crosstalk Analysis
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:11|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the images out for ImageJ to export the pixel data.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:MaskedGFP
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:GFP
    Enter single file name:OrigBlue
    Do you want to add a suffix to the image file name?:No
    Text to append to the image name: (\\\\g<Strain> \\\\g<Colony> \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CMasked Smoothed Images for Crosstalk Analysis
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No
