CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130723021150

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load each channel of the image to be analyzed this round.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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

LoadImages:[module_num:2|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load cell, nuclei, mitochondria, and cytosol objects.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
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
    Text that these images have in common (case-sensitive):Cytoplasm (
    Position of this image in each group:4
    Extract metadata from where?:File name
    Regular expression that finds metadata in the file name:\\\\((?P<Strain>.*) - (?P<Field>\\\\S*)\\\\)
    Type the regular expression that finds metadata in the subfolder path:.*\x5B\\\\\\\\/\x5D(?P<Date>.*)\x5B\\\\\\\\/\x5D(?P<Run>.*)$
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Objects
    Name this loaded image:CytosolImage
    Name this loaded object:Cytoplasm
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

ImageMath:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Apply crosstalk correction for NLStdTom and MTSmCer signal appearing in GFP channel. These values are the slope of the linear regression line from the GFP pixel intensity vs. each channel individually.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Hidden:1
    Select an image to measure:GFPFilteredCrosstalkCorrected
    Select objects to measure:Cells
    Select objects to measure:Nuclei
    Select objects to measure:Mitochondria
    Select objects to measure:Cytoplasm

CalculateMath:[module_num:8|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Subtract the mean compartment background fluoresence. This value is determined from the mean GFP intensity for the compartments in cells expressing the marker proteins but not GFP.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:CellsMeanGFPCorrected
    Operation:None
    Select the numerator measurement type:Object
    Select the numerator objects:Cells
    Select the numerator measurement:Intensity_MeanIntensity_GFPFilteredCrosstalkCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the second operand measurement type:Image
    Select the second operand objects:None
    Select the second operand measurement:None
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:-0.0041092
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:9|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Subtract the mean compartment background fluoresence. This value is determined from the mean GFP intensity for the compartments in cells expressing the marker proteins but not GFP.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:NucleiMeanGFPCorrected
    Operation:None
    Select the numerator measurement type:Object
    Select the numerator objects:Nuclei
    Select the numerator measurement:Intensity_MeanIntensity_GFPFilteredCrosstalkCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the second operand measurement type:Image
    Select the second operand objects:None
    Select the second operand measurement:None
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:-0.0040072
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:10|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Subtract the mean compartment background fluoresence. This value is determined from the mean GFP intensity for the compartments in cells expressing the marker proteins but not GFP.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:MitochondriaMeanGFPCorrected
    Operation:None
    Select the numerator measurement type:Object
    Select the numerator objects:Mitochondria
    Select the numerator measurement:Intensity_MeanIntensity_GFPFilteredCrosstalkCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the second operand measurement type:Image
    Select the second operand objects:None
    Select the second operand measurement:None
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:-0.0044924
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:11|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Subtract the mean compartment background fluoresence. This value is determined from the mean GFP intensity for the compartments in cells expressing the marker proteins but not GFP.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:CytoplasmMeanGFPCorrected
    Operation:None
    Select the numerator measurement type:Object
    Select the numerator objects:Cytoplasm
    Select the numerator measurement:Intensity_MeanIntensity_GFPFilteredCrosstalkCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the second operand measurement type:Image
    Select the second operand objects:None
    Select the second operand measurement:None
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:-0.0040117
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:12|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:NucleiLeakageCorrectedHalf
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Nuclei
    Select the minuend measurement:Math_NucleiMeanGFPCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Mitochondria
    Select the subtrahend measurement:Math_MitochondriaMeanGFPCorrected
    Multiply the above operand by:0.091069
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:13|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:NucleiLeakageCorrected
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Nuclei
    Select the minuend measurement:Math_NucleiLeakageCorrectedHalf
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Cytoplasm
    Select the subtrahend measurement:Math_CytoplasmMeanGFPCorrected
    Multiply the above operand by:0.632248
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:14|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:MitochondriaLeakageCorrectedHalf
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Mitochondria
    Select the minuend measurement:Math_MitochondriaMeanGFPCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Nuclei
    Select the subtrahend measurement:Math_NucleiMeanGFPCorrected
    Multiply the above operand by:0.02605555
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:15|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:MitochondriaLeakageCorrected
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Mitochondria
    Select the minuend measurement:Math_MitochondriaLeakageCorrectedHalf
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Cytoplasm
    Select the subtrahend measurement:Math_CytoplasmMeanGFPCorrected
    Multiply the above operand by:0.88097
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:16|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:CytoplasmlLeakageCorrectedHalf
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Cytoplasm
    Select the minuend measurement:Math_CytoplasmMeanGFPCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Nuclei
    Select the subtrahend measurement:Math_NucleiMeanGFPCorrected
    Multiply the above operand by:0.01954255
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:No
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:17|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Correct for signal which leaks into other compartments. This value is derived from half the slope of the linear regression line between the signal intensity of a compartment containing a specifically-localized GFP protein vs. the signal detected in each other compartment.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:CytoplasmLeakageCorrected
    Operation:Subtract
    Select the minuend measurement type:Object
    Select the minuend objects:Cytoplasm
    Select the minuend measurement:Math_CytoplasmlLeakageCorrectedHalf
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the subtrahend measurement type:Object
    Select the subtrahend objects:Mitochondria
    Select the subtrahend measurement:Math_MitochondriaMeanGFPCorrected
    Multiply the above operand by:0.08231155
    Raise the power of above operand by:1
    Take log10 of result?:No
    Multiply the result by:1
    Raise the power of result by:1
    Add to the result:0
    Constrain the result to a lower bound?:Yes
    Set values less than this to this value?:0
    Constrain the result to an upper bound?:No
    Set values greater than this to this value?:1

CalculateMath:[module_num:18|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Compute the total signal detected in the two compartments to be examined, nucleus and mitochondria.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:NMLocalizationSum
    Operation:Add
    Select the first operand measurement type:Object
    Select the first operand objects:Nuclei
    Select the first operand measurement:Math_NucleiLeakageCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the second operand measurement type:Object
    Select the second operand objects:Mitochondria
    Select the second operand measurement:Math_MitochondriaLeakageCorrected
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

CalculateMath:[module_num:19|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Divide the nuclear signal by the total nuclear and mitochondrial signal to produce the localization index.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:NMLocalizationIndex
    Operation:Divide
    Select the numerator measurement type:Object
    Select the numerator objects:Nuclei
    Select the numerator measurement:Math_NucleiLeakageCorrected
    Multiply the above operand by:1
    Raise the power of above operand by:1
    Select the denominator measurement type:Object
    Select the denominator objects:Nuclei
    Select the denominator measurement:Math_NMLocalizationSum
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

ExportToSpreadsheet:[module_num:20|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the data.\', \'Q-SCAn Program\x3A The exported metadata fields will be overridden unless the manual setting is checked. Do not change the output file name unelss you turn off success detection.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
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
    Press button to select measurements to export:Cytoplasm\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected,Cytoplasm\x7CMath_CytoplasmMeanGFPCorrected,Mitochondria\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected,Mitochondria\x7CMath_MitochondriaMeanGFPCorrected,Mitochondria\x7CMath_MitochondriaLeakageCorrected,Nuclei\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected,Nuclei\x7CMath_NucleiMeanGFPCorrected,Nuclei\x7CMath_NucleiLeakageCorrected,Nuclei\x7CMath_NMLocalizationIndex,Nuclei\x7CMath_NMLocalizationSum,Cells\x7CIntensity_MeanIntensity_GFPFilteredCrosstalkCorrected,Cells\x7CMath_CellsMeanGFPCorrected,Image\x7CMetadata_Strain,Image\x7CMetadata_Field
    Data to export:Cells
    Combine these object measurements with those of the previous object?:No
    File name:Compartment Localization Data.csv
    Use the object name for the file name?:No
    Data to export:Nuclei
    Combine these object measurements with those of the previous object?:Yes
    File name:Nuclei GFP Intensities.csv
    Use the object name for the file name?:No
    Data to export:Mitochondria
    Combine these object measurements with those of the previous object?:Yes
    File name:DATA.csv
    Use the object name for the file name?:Yes
    Data to export:Cytoplasm
    Combine these object measurements with those of the previous object?:Yes
    File name:DATA.csv
    Use the object name for the file name?:Yes
