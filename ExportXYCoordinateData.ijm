////// Export XY Coordinate Data
//////
////// An ImageJ macro which exports the XY coordinate data for all
////// images in a directory and its subdirectories (only 1 level) into
////// files with the same name and the extension ".txt".
//////
////// Copyright 2012 Nicholas Bauer
////// www.nicholasbauer.com


//// execution: ////
setBatchMode(true);    // Prevents the images from actually being displayed.

// Retrieve the image sequences
dir = getDirectory("Select a directory containing the images.");
list = getFileList(dir);
dir = substring(dir, 0, lengthOf(dir) - 1);

// For each channel, load all the images and export them
for (i = 0; i<list.length; i++) {
    child = dir + File.separator + list[i];
    if (File.isDirectory(child)) {
        childList = getFileList(child);
        for (j = 0; j<childList.length; j++) {
            file = child+File.separator+childList[j];
	if (!endsWith(file, ".txt")) {
                open(file);
                run("Save XY Coordinates...", "background=-1 save=["+file+".txt]");
                close();
            }
        }
    } else {
        file = child;
        if (!endsWith(file, ".txt")) {
            open(file);
            run("Save XY Coordinates...", "background=-1 save=["+file+".txt]");
            close();
        }
    }
}

setBatchMode(false);    // Reset to normal function.
