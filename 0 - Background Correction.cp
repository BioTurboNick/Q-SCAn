CellProfiler Pipeline: http://www.cellprofiler.org
Version:2
DateRevision:20130614030205

LoadImages:[module_num:1|svn_version:\'Unknown\'|variable_revision_number:11|show_window:False|notes:\x5B\'Load each channel of the image to be analyzed this round.\', \'Q-SCAn Program\x3A The metadata fields will be overridden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    File type to be loaded:individual images
    File selection method:Text-Exact match
    Number of images in each group?:3
    Type the text that the excluded images have in common:Median
    Analyze all subfolders within the selected folder?:All
    Input image file location:Default Input Folder sub-folder\x7CInput Images
    Check image sets for unmatched or duplicate files?:Yes
    Group images by metadata?:No
    Exclude certain files?:Yes
    Specify metadata fields to group by:
    Select subfolders to analyze:
    Image count:4
    Text that these images have in common (case-sensitive):ChD-T3
    Position of this image in each group:1
    Extract metadata from where?:Path
    Regular expression that finds metadata in the file name:
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Field (?P<Field>\\\\S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:DICUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch3-T1
    Position of this image in each group:2
    Extract metadata from where?:Path
    Regular expression that finds metadata in the file name:
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Field (?P<Field>\\\\S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:NLStdTomUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch2-T3
    Position of this image in each group:3
    Extract metadata from where?:Path
    Regular expression that finds metadata in the file name:((?P<Strain>.*) - (?P<Field>S*))
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Field (?P<Field>\\\\S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:MTSmCerUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No
    Text that these images have in common (case-sensitive):Ch2-T2
    Position of this image in each group:4
    Extract metadata from where?:Path
    Regular expression that finds metadata in the file name:((?P<Strain>.*) - (?P<Field>S*))
    Type the regular expression that finds metadata in the subfolder path:.*\\\\\\\\(?P<Strain>.*) - Field (?P<Field>\\\\S*).lsm
    Channel count:1
    Group the movie frames?:No
    Grouping method:Interleaved
    Number of channels per group:3
    Load the input as images or objects?:Images
    Name this loaded image:GFPUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outline image:LoadedImageOutlines
    Channel number:1
    Rescale intensities?:No

RescaleIntensity:[module_num:2|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC input image from the 16-bit 0-1 range to the 12-bit 0-1 range. This is necessary because the images are stored as a 16-bit TIFF but the data is 12-bit.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICUnscaled
    Name the output image:DIC
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
    Enter the divisor:0.062486
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:3|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC input image from the 16-bit 0-1 range to the 12-bit 0-1 range. This is necessary because the images are stored as a 16-bit TIFF but the data is 12-bit.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:NLStdTomUnscaled
    Name the output image:NLStdTom
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
    Enter the divisor:0.062486
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:4|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC input image from the 16-bit 0-1 range to the 12-bit 0-1 range. This is necessary because the images are stored as a 16-bit TIFF but the data is 12-bit.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MTSmCerUnscaled
    Name the output image:MTSmCer
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
    Enter the divisor:0.062486
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:5|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC input image from the 16-bit 0-1 range to the 12-bit 0-1 range. This is necessary because the images are stored as a 16-bit TIFF but the data is 12-bit.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:GFPUnscaled
    Name the output image:GFP
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
    Enter the divisor:0.062486
    Select the measurement to use as a divisor:None

LoadSingleImage:[module_num:6|svn_version:\'Unknown\'|variable_revision_number:5|show_window:False|notes:\x5B\'Load the background correction (median dark current, and median DIC shading) images.\', \'Q-SCAn Program\x3A The first entry must be the brightfield shading image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Input image file location:Default Input Folder sub-folder\x7CInput Images
    Filename of the image to load (Include the extension, e.g., .tif):Brightfield Median.tif
    Load as images or objects?:Images
    Name the image that will be loaded:MedianShadingDICUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outlines:NucleiOutlines
    Rescale intensities?:No
    Filename of the image to load (Include the extension, e.g., .tif):Dark Current ChD-T3 Median.tif
    Load as images or objects?:Images
    Name the image that will be loaded:MedianDarkCurrentDICUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outlines:NucleiOutlines
    Rescale intensities?:No
    Filename of the image to load (Include the extension, e.g., .tif):Dark Current Ch3-T1 Median.tif
    Load as images or objects?:Images
    Name the image that will be loaded:MedianDarkCurrentNLStdTomUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outlines:NucleiOutlines
    Rescale intensities?:No
    Filename of the image to load (Include the extension, e.g., .tif):Dark Current Ch2-T3 Median.tif
    Load as images or objects?:Images
    Name the image that will be loaded:MedianDarkCurrentMTSmCerUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outlines:NucleiOutlines
    Rescale intensities?:No
    Filename of the image to load (Include the extension, e.g., .tif):Dark Current Ch2-T2 Median.tif
    Load as images or objects?:Images
    Name the image that will be loaded:MedianDarkCurrentGFPUnscaled
    Name this loaded object:Nuclei
    Retain outlines of loaded objects?:No
    Name the outlines:NucleiOutlines
    Rescale intensities?:No

RescaleIntensity:[module_num:7|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC dark current background correction input image from the 16-bit 0-65535 range to the 12-bit 0-1 range. This is necessary because ImageJ outputs a 32-bit TIFF and CellProfiler is unable to scale them.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MedianDarkCurrentDICUnscaled
    Name the output image:MedianDarkCurrentDIC
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
    Enter the divisor:4095
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:8|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the DIC shading background correction input image from the 16-bit 0-65535 range to the 12-bit 0-1 range. This is necessary because ImageJ outputs a 32-bit TIFF and CellProfiler is unable to scale them.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MedianShadingDICUnscaled
    Name the output image:MedianShadingDIC
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
    Enter the divisor:4095
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:9|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the NLStdTom dark current background correction input image from the 16-bit 0-65535 range to the 12-bit 0-1 range. This is necessary because ImageJ outputs a 32-bit TIFF and CellProfiler is unable to scale them.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MedianDarkCurrentNLStdTomUnscaled
    Name the output image:MedianDarkCurrentNLStdTom
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
    Enter the divisor:4095
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:10|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the MTSmCer dark current background correction input image from the 16-bit 0-65535 range to the 12-bit 0-1 range. This is necessary because ImageJ outputs a 32-bit TIFF and CellProfiler is unable to scale them.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MedianDarkCurrentMTSmCerUnscaled
    Name the output image:MedianDarkCurrentMTSmCer
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
    Enter the divisor:4095
    Select the measurement to use as a divisor:None

RescaleIntensity:[module_num:11|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Rescale the GFP dark current background correction input image from the 16-bit 0-65535 range to the 12-bit 0-1 range. This is necessary because ImageJ outputs a 32-bit TIFF and CellProfiler is unable to scale them.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:MedianDarkCurrentGFPUnscaled
    Name the output image:MedianDarkCurrentGFP
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
    Enter the divisor:4095
    Select the measurement to use as a divisor:None

ImageMath:[module_num:12|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Step 1 of DIC background correction\x3A Subtract the DIC dark current image from the DIC image. Negative values are not being forced to zero here. That will be done in Step 3.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:No
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:DICMinusMedianDarkCurrentDIC
    Image or measurement?:Image
    Select the first image:DIC
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianDarkCurrentDIC
    Multiply the second image by:1
    Measurement:

ImageMath:[module_num:13|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Step 2 of DIC background correction\x3A Subtract the DIC dark current image from the DIC shading image. Negative values are not being forced to zero here. That will be done in Step 3.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:No
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:MedianShadingDICMinusMedianDarkCurrentDIC
    Image or measurement?:Image
    Select the first image:MedianShadingDIC
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianDarkCurrentDIC
    Multiply the second image by:1
    Measurement:

MeasureImageIntensity:[module_num:14|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Measure the intensity of the background correction image so that the DIC shading-corrected image can be scaled appropriately.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the image to measure:MedianShadingDICMinusMedianDarkCurrentDIC
    Measure the intensity only from areas enclosed by objects?:No
    Select the input objects:None

ImageMath:[module_num:15|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Step 3 of DIC background correction\x3A Divide the dark current-corrected DIC image by the dark current-corrected DIC shading image.\', \'Values above 1 are not being forced to 1 here. This will be done in Step 4.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Divide
    Raise the power of the result by:1
    Multiply the result by:1.0
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:No
    Ignore the image masks?:No
    Name the output image:DICAlmostCorrected
    Image or measurement?:Image
    Select the first image:DICMinusMedianDarkCurrentDIC
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianShadingDICMinusMedianDarkCurrentDIC
    Multiply the second image by:1
    Measurement:

CalculateMath:[module_num:16|svn_version:\'Unknown\'|variable_revision_number:2|show_window:False|notes:\x5B\'Determine the factor by which to multiply the corrected DIC image to bring the average intensity into line with the original image. This is equal to the inverse of the average intensity of the dark current-corrected image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Name the output measurement:DICAdjustmentFactor
    Operation:None
    Select the numerator measurement type:Image
    Select the numerator objects:None
    Select the numerator measurement:Intensity_MeanIntensity_MedianShadingDICMinusMedianDarkCurrentDIC
    Multiply the above operand by:1
    Raise the power of above operand by:-1.0
    Select the second operand measurement type:Image
    Select the second operand objects:None
    Select the second operand measurement:None
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

RescaleIntensity:[module_num:17|svn_version:\'6746\'|variable_revision_number:2|show_window:False|notes:\x5B\'Adjust the DIC correction image so that the average intensity of the final image equals the average intensity of the original image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the input image:DICAlmostCorrected
    Name the output image:DICCorrected
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
    Enter the divisor:0.062486
    Select the measurement to use as a divisor:Math_DICAdjustmentFactor

ImageMath:[module_num:18|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5Bu\'Perform background correction on the NLS-tdTom image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:NLStdTomCorrected
    Image or measurement?:Image
    Select the first image:NLStdTom
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianDarkCurrentNLStdTom
    Multiply the second image by:1
    Measurement:

ImageMath:[module_num:19|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Perform background correction on the MTS-mCer image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:MTSmCerCorrected
    Image or measurement?:Image
    Select the first image:MTSmCer
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianDarkCurrentMTSmCer
    Multiply the second image by:1
    Measurement:

ImageMath:[module_num:20|svn_version:\'Unknown\'|variable_revision_number:3|show_window:False|notes:\x5B\'Perform background correction on the GFP image.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Operation:Subtract
    Raise the power of the result by:1
    Multiply the result by:1
    Add to result:0
    Set values less than 0 equal to 0?:Yes
    Set values greater than 1 equal to 1?:Yes
    Ignore the image masks?:No
    Name the output image:GFPCorrected
    Image or measurement?:Image
    Select the first image:GFP
    Multiply the first image by:1
    Measurement:
    Image or measurement?:Image
    Select the second image:MedianDarkCurrentGFP
    Multiply the second image by:1
    Measurement:

SaveImages:[module_num:21|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected DIC image.\', \'Note that the idea here is to convert whatever the initial arbitrary filename format is to a common form, to reduce the number of changes necessary.\', \'Q-SCAn Program\x3A The suffix will be overriden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:DICCorrected
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:DICUnscaled
    Enter single file name:
    Do you want to add a suffix to the image file name?:Yes
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CCorrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:22|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected NLS-tdTom image.\', \'Note that the idea here is to convert whatever the initial arbitrary filename format is to a common form, to reduce the number of changes necessary.\', \'Q-SCAn Program\x3A The suffix will be overriden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:NLStdTomCorrected
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:NLStdTomUnscaled
    Enter single file name:
    Do you want to add a suffix to the image file name?:Yes
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CCorrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:23|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected MTS-mCer image.\', \'Note that the idea here is to convert whatever the initial arbitrary filename format is to a common form, to reduce the number of changes necessary.\', \'Q-SCAn Program\x3A The suffix will be overriden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:MTSmCerCorrected
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:MTSmCerUnscaled
    Enter single file name:
    Do you want to add a suffix to the image file name?:Yes
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CCorrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No

SaveImages:[module_num:24|svn_version:\'Unknown\'|variable_revision_number:7|show_window:False|notes:\x5B\'Save the corrected GFP image.\', \'Note that the idea here is to convert whatever the initial arbitrary filename format is to a common form, to reduce the number of changes necessary.\', \'Q-SCAn Program\x3A The suffix will be overriden unless the manual setting is checked.\'\x5D|batch_state:array(\x5B\x5D, dtype=uint8)]
    Select the type of image to save:Image
    Select the image to save:GFPCorrected
    Select the objects to save:None
    Select the module display window to save:None
    Select method for constructing file names:From image filename
    Select image name for file prefix:GFPUnscaled
    Enter single file name:
    Do you want to add a suffix to the image file name?:Yes
    Text to append to the image name: (\\\\g<Strain> - \\\\g<Field>)
    Select file format to use:tif
    Output file location:Default Output Folder sub-folder\x7CCorrected Images
    Image bit depth:16
    Overwrite existing files without warning?:Yes
    Select how often to save:Every cycle
    Rescale the images? :No
    Save as grayscale or color image?:Grayscale
    Select colormap:gray
    Store file and path information to the saved image?:No
    Create subfolders in the output folder?:No
