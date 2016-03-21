CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130109170729

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5Bu\'Load each channel of the image to be analyzed this round.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Text that these images have in common (case-sensitive):Ch3-T1
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) (?P<Condition>.*) (?P<Field>.*).lsm
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) (?P<Condition>.*) (?P<Field>.*).lsm
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) (?P<Condition>.*) (?P<Field>.*).lsm
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
    Rescale intensities?:No

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load cell, nuclei, mitochondria, and cytosol objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Image count:4
    Text that these images have in common (case-sensitive):Cells Filtered (
    Position of this image in each group:1
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
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
    Text that these images have in common (case-sensitive):Pure Nuclei (
    Position of this image in each group:2
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:NucleiImage
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Pure Mitochondria (
    Position of this image in each group:3
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:MitochondriaImage
    Name this loaded object:Mitochondria
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Cytosol (
    Position of this image in each group:4
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) (?P<Colony>\\\\S*) (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:CytosolImage
    Name this loaded object:Cytosol
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No

Smooth:[module_num:3|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove the influence of noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTom
    Name the output image:NLStdTomFiltered
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

Smooth:[module_num:4|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove the influence of noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCer
    Name the output image:MTSmCerFiltered
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

Smooth:[module_num:5|svn_version:\'Unknown\'|variable_revision_number:1|show_window:False|notes:\x5B\'Smooth the image subtly to remove the influence of noise.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:GFP
    Name the output image:GFPFiltered
    Select smoothing method:Median Filter
    Calculate artifact diameter automatically?:No
    Typical artifact diameter, in  pixels:2
    Edge intensity difference:0.1

ImageMath:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Apply crosstalk correction for NLStdTom and MTSmCer signal appearing in GFP channel.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Add
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:GFPFilteredCrosstalkCorrected
    Image or measurement?:Image
    Select the first image:GFPFiltered
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:NLStdTomFiltered
    Multiply the second image by:-0.0145417
    Measurement:
    Image or measurement?:Image
    Select the third image:MTSmCerFiltered
    Multiply the third image by:-0.0838191
    Measurement:

MeasureObjectIntensity:[module_num:7|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Hidden:3
    Select an image to measure:GFPFilteredCrosstalkCorrected
    Select an image to measure:NLStdTomFiltered
    Select an image to measure:MTSmCerFiltered
    Select objects to measure:Cells
    Select objects to measure:Nuclei
    Select objects to measure:Mitochondria
    Select objects to measure:Cytosol

ExportToSpreadsheet:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the data.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Press button to select measurements to export:Mitochondria\x7CIntensity_MeanIntensity_MTSmCerFiltered,Mitochondria\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected,Nuclei\x7CIntensity_MeanIntensity_NLStdTomFiltered,Nuclei\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected
    Data to export:Nuclei
    Combine these object measurements with those of the previous object?:No
    File name:Marker Target Correlation Data.csv
    Use the object name for the file name?:No
    Data to export:Mitochondria
    Combine these object measurements with those of the previous object?:Yes
    File name:Nuclei GFP Intensities.csv
    Use the object name for the file name?:No
