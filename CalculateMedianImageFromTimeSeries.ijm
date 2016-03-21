////// Calculate Median Image From Time Series
//////
////// An ImageJ macro which calculates the median image from a time series
////// image in a directory of the form "Image.lsm\Image_Time_Channel.tif" and
////// saves it as "Image Channel Median.tif"
//////
////// Copyright 2012 Nicholas Bauer
////// www.nicholasbauer.com

/// mapping of time series channel names to real channel names ///
original = newArray("c001", "c002", "c003", "c004");
final = newArray("Ch3-T1", "Ch2-T2", "Ch2-T3", "ChD-T3");



//// execution: ////
setBatchMode(true);    // Prevents the images from actually being displayed.

// Retrieve the image sequences
dir = getArgument();
if (dir == "") {
    dir = getDirectory("Select the directory containing the image sequence.");
    dir = substring(dir, 0, lengthOf(dir) - 1);
}

parentDir = substring(dir, 0, lastIndexOf(dir, File.separator) + 1);
dirPrefix = substring(dir, lastIndexOf(dir, File.separator) + 1, lastIndexOf(dir, "."));
list = getFileList(dir);

// Find the channels
foundChannel = 0;
channels = newArray("");
for (i = 0; i<list.length; i++) {
    if (!foundChannel) {
        channel = substring(list[i], lastIndexOf(list[i], "_") + 1, lastIndexOf(list[i], "."));
        
        for (j = 0; j<channels.length; j++) {
            if (channels[j] == channel) {
                foundChannel = 1;
            }
        }

        if (!foundChannel) {
            if (channels[0] == "") {
                channels[0] = channel;
            }
            else {
                channels = Array.concat(channels, channel);
            }
        }
    }
}

// For each channel, load all the images and export them
for (i = 0; i<channels.length; i++) {
    channel = channels[i];
    for (j = 0; j<list.length; j++) {
        nextChannel = substring(list[j], lastIndexOf(list[j], "_") + 1, lastIndexOf(list[j], "."));
        if (nextChannel == channel) {
            open(dir + File.separator + list[j]);
        }
    }

    run("Images to Stack", "name=["+dirPrefix+" "+channel+" Stack] title=["+channel+"]");

    // Look up what the output channel name should be
    for (j = 0; j<original.length; j++) {
        if (original[j] == channel) {
            channel = final[j];
        }
    }

    run("Z Project...", "start=[] stop=[] projection=Median");
    saveAs("Tiff", parentDir+File.separator+dirPrefix+" "+channel+" Median");
    close(); // close the Median image
    close(); // close the Stack image
}

setBatchMode(false);    // Reset to normal function.
