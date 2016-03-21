////// Open And Export Channels
//////
////// An ImageJ macro which exports every channel of every image
////// in a specified directory as TIFF files into subdirectories of
////// the form "Images\Exported TIFFs\ImageName\ChannelName.tif".
//////
////// It may also take a command line parameter of the form 
////// "ImagePath|OutputPath". If "|OutputPath" is omitted, the images will
////// be saved to the "Images\Exported TIFFs" directory. These paths should
////// omit a terminal path separator character (e.g. "\").
//////
////// Copyright 2012 Nicholas Bauer
////// www.nicholasbauer.com


//// variables: ////
exportDirString = "Exported TIFFs"    // Suffix added to specify the exported files


//// execution: ////
setBatchMode(true);    // Prevents the images from actually being displayed.

// Retrieve the image directories
args = getArgument();
if (args == "") {
    dir = getDirectory("What directory are the images in?");
    exportDir = dir+exportDirString;
} else {
    if (indexOf(args, "|") <= 0 || indexOf(args, "|") == lengthOf(args) - 1) { // If there is no Output Path parameter provided
        dir = args;
        exportDir = dir+File.separator+exportDirString;
    } else {
        dir = substring(args, 0, indexOf(args, "|"));
        exportDir = substring(args, indexOf(args, "|") + 1, lengthOf(args));
    }
    dir += File.separator;
}
exportDir += File.separator;

list = getFileList(dir);
File.makeDirectory(exportDir);

// For each item in the directory, as long as it is not also a directory,
// export it (or its separate channels) as TIFF files
for (i=0; i<list.length; i++) {
    currItem = dir+list[i];

    if (File.isDirectory(currItem) == 0 && !endsWith(currItem, ".txt") && !endsWith(currItem, ".lut")  && !endsWith(currItem, ".roi") && !endsWith(currItem, ".mdb")) {    // Only process if it is an image file.
        // Open the item, export its channels, and close it.
        open(currItem);
        imageExportDir = exportDir+getTitle();
        File.makeDirectory(imageExportDir);
        getDimensions(w, h, nChannels, s, f);    // Determine how many channels the file has
        if (nChannels > 1) {    // We have to use a different function if the image has more than one channel
            run("Image Sequence... ", "format=TIFF use save=["+imageExportDir+"]");
        } else {
            saveAs("Tiff", imageExportDir+File.separator+getTitle());
        }
        close();
    }
}

setBatchMode(false);    // Reset to normal function.
