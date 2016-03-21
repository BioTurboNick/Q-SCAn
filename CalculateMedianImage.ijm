////// Calculate Median Image
//////
////// An ImageJ macro which calculates the median image from a series
////// of images in directories of the form "Image 1.lsm\Channel.tif" or
////// of the form "Image 1.lsm\Image 1.tif" and saves it as "Image Median.tif"
////// or "Image Channel Median.tif", respectively.
//////
////// Copyright 2012 Nicholas Bauer
////// www.nicholasbauer.com


//// execution: ////
setBatchMode(true);    // Prevents the images from actually being displayed.

// Retrieve the image sequences
dir = getArgument();
if (dir == "") {
    dir = getDirectory("Select a directory containing a member of the image sequence.");
    dir = substring(dir, 0, lengthOf(dir) - 1);
}

parentDir = substring(dir, 0, lastIndexOf(dir, File.separator) + 1);
dirPrefix = substring(dir, lastIndexOf(dir, File.separator) + 1,  lastIndexOf(dir, " "));
list = getFileList(dir);
parentDirList = getFileList(parentDir);

if (startsWith(list[0], dirPrefix)) {
    singleMode = 1;    // When the file has the same prefix as the directory, we need to treat it differently.
} else {
    singleMode = 0;
}

// For each directory with the same prefix, open all the images within them.
for (i=0; i<parentDirList.length; i++) {
    currItem = parentDir + parentDirList[i];
    if (lastIndexOf(parentDirList[i], " ") > 0) {
        if (File.isDirectory(currItem) == 1 && substring(parentDirList[i], 0, lastIndexOf(parentDirList[i], " ")) == dirPrefix) {    // Only process if it is a directory with the intended prefix.
            if (singleMode) {
                fileList = getFileList(currItem);
                open(currItem + fileList[0]);
            } else {
                for (j = 0; j<list.length; j++) {
                    currFile = currItem + list[j];
                    open(currFile);
                }
            }
       }
    }
}

// For each image series, form a stack, calculate the median, and save it.
for (i = 0; i<list.length; i++) {
    if (singleMode) {    // If the file starts the same as the directory prefix, the prefix is the same.
        prefix = dirPrefix;
        filePrefix = prefix;
    } else {
        filePrefix = substring(list[i], 0, lastIndexOf(list[i], "."));
        prefix = dirPrefix+" "+filePrefix;
    }

    run("Images to Stack", "name=Stack title="+filePrefix);
    run("Z Project...", "start=[] stop=[] projection=Median");
    saveAs("Tiff", parentDir+File.separator+prefix+" Median");
    close(); // close the Median image
    close(); // close the Stack image
}

setBatchMode(false);    // Reset to normal function.
