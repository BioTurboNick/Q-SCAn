CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130716190332

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the fluorescence channels used for compartment identification.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Colony (?P<Colony>.*) - Field (?P<Field>.*).lsm
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
    Text that these images have in common (case-sensitive):Ch2-T3
    Position of this image in each group:2
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
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
    Rescale intensities?:Yes

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load the cell objects.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Colony>\\\\S*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:DNA
    Name this loaded object:Cells
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:Yes

RescaleIntensity:[module_num:3|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Normalize the image so that the mean of the intensities within cells for the fluorophor = 0.01. This value is determined by dividing the cross-dataset intensity sum and area sum to find the mean cellular intensity for the marker. This number must be multiplied by 100 and entered here.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTom
    Name the output image:NLStdTomNormalized
    Select rescaling method:Divide each image by the same value
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
    Enter the divisor:1.101399543
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:4|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Normalize the image so that the mean of the intensities within cells for the fluorophor = 0.01. This value is determined by dividing the cross-dataset intensity sum and area sum to find the mean cellular intensity for the marker. This number must be multiplied by 100 and entered here.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCer
    Name the output image:MTSmCerNormalized
    Select rescaling method:Divide each image by the same value
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
    Enter the divisor:0.730259059
    Select the measurement to use as a divisor:None

MeasureObjectIntensity:[module_num:5|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Hidden:2
    Select an image to measure:NLStdTomNormalized
    Select an image to measure:MTSmCerNormalized
    Select objects to measure:Cells

ExportToSpreadsheet:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select or enter the column delimiter:Comma (",")
    Prepend the output file name to the data file names?:Yes
    Add image metadata columns to your object data file?:Yes
    Limit output to a size that is allowed in Excel?:No
    Select the columns of measurements to export?:No
    Calculate the per-image mean values for object measurements?:No
    Calculate the per-image median values for object measurements?:No
    Calculate the per-image standard deviation values for object measurements?:No
    Output file location:Default Output Folder sub-folder\x7COutput Data
    Create a GenePattern GCT file?:No
    Select source of sample row name:Metadata
    Select the image to use as the identifier:None
    Select the metadata to use as the identifier:None
    Export all measurements, using default file names?:No
    Press button to select measurements to export:
    Data to export:Image
    Combine these object measurements with those of the previous object?:No
    File name:Filtering Analysis Image Data.csv
    Use the object name for the file name?:No
    Data to export:Cells
    Combine these object measurements with those of the previous object?:No
    File name:Filtering Analysis Cell Intensity Data.csv
    Use the object name for the file name?:No
