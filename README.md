# Macros


## ROOT Macros

addTwoHists.C
Adds Sr and Y spectra from simulation to compare to data.

plotResults.C/plotResults.h
Compares 2-5 datasets.

simcompare_with_ij2root.C
Converts the ImageJ-generated ascii file to a root file, and compares simulation data to experimental data.

vectortest.C
Minimal example of adding a C++ vector to a ROOT TTree.


## ImageJ Macros

getAverage.txt
Gets the average of all images in a run.

subtractAvg.txt
Subtracts the average from every image, and stores the subtracted images in a folder called sub.

gaussianBlur.txt
Blurs the subtracted images, and stores the blurred images in a folder called blur, parallel to sub.

getResults2.txt
Generates the ascii file used by simcompare_with_ij2root.C.

eventFinder.ijm
Sorts frames into ones with events and ones without events, and stores them in subfolders of blur called events and noevents.
