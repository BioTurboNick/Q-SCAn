QSCAn Readme
=========================================================
Author: Nicholas Bauer
(c) 2014 Emory University

Bauer, N. C., Corbett, A. H., and Doetsch, P. W. (2013)
Automated quantification of the subcellular localization of multicompartment proteins via Q-SCAn.
Traffic 14(12):1200-1208.
http://dx.doi.org/10.1111/tra.12118

=========================================================

Change Log
==========
1.0.2.0 - Corrected an error in the background correction pipeline to work around a CellProfiler bug, and added scroll bars to the settings windows to allow for smaller screens.
1.0.1.0 - Corrected some issues with identifing the proper directories for ImageJ and CellProfiler de novo, added button to access this file, and adjusted for the final 2.1 release of CellProfiler.
1.0.0.1 - Corrected minor issue with the Check Success setting binding.

Requirements
============
CellProfiler 2.1
ImageJ 1.48 -- http://imagej.nih.gov/ij/download.html

General Instructions
====================
1. Download and install CellProfiler 2.1 and ImageJ 1.48.	
2. Create a working directory which will contain all of the files generated. (e.g. c:\QSCAn\)
3. Extract the files into the working directory.
4. Move or copy the files in the "CellProfiler Plugins" folder to the plugins directory shown on the
   CellProfiler preferences window (File > Preferences...)
	Alternatively, you can tell CellProfiler that the "CellProfiler Plugins" folder is its plugin
	directory.
5. Set up the CellProfiler pipelines for your particular work.
	If you are using yeast cells, nuclei, and mitochondria, minimal changes may be necessary.
		e.g. changing the metadata fields for loading and saving images
		Metadata example: Strain B - Field 2.lsm
			can be encoded by Strain (?P<Strain>.*) - Field (?P<Field>\S*).lsm
			where Strain = B and Field = 2
		These are composed from "Regular Expressions"
			(?P<metadata_name>_____) where _____ is replaced by the expression.
			.* = all characters \S* = all non-whitespace characters
		When you remove or add a metadata field or change its name, you will need to go to any ExportToSpreadsheet module and click "Press to Select Measurements" to allow it to discover the changes and/or so you can add the new metadata record.
	You can usually ignore errors in LoadData, FilterObjects, etc. that relate to not finding files, as the default input folders often won't match the ones used during the run.
	If you are doing something differently, you'll need to adapt the pipelines to your specific needs.
6. You may need to adjust the ImageJ macros.
	They are geared towards processing images saved in the Zeiss ".lsm" format with a space separating
	the name and the number for the correction images.

Fully Automated (Windows only)
========================
1. After the above is set up, launch QSCAn.exe.
2. Click "Setup..." and adjust settings. These will be saved.
3. Select the source image directory (e.g. c:\Raw Images\11-01-12\). These should be the raw microscope files (e.g. *.lsm)
4. Click "Start Run"
5. The program will launch ImageJ in batch mode (no UI) to export the images to the working directory
   (e.g. c:\QSCAn\Analysis\11-01-12 Analysis\Input Images\)
6. The program will then run ImageJ to produce the shading and dark current correction images, save them in the working
   directory, and delete the exported correction images from the working directory.
7. The program will then run CellProfiler in headless mode (no UI, but minimized command line), with each pipeline in sequence:
	0 - Background Correction
	1 - Identify Cells and Background
	2 - Measure Image Intensities and Finish Correction
	3 - Filter Cells and Identify Compartments
	4 - Calculate Localization Index and Export Intensity Data
8. Between pipelines 2 and 3, the program examines the within-cell intensities and averages them over the dataset,
   then exports that information to be used by pipeline 3 to normalize the intensities (only for compartment markers).
9. Data is saved to *.csv files in the working directory (e.g. c:\QSCAn\Analysis\11-01-12 Analysis\Output Data\)