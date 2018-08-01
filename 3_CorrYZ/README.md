Once you have produced all the xyzCorrection trees, you will need to merge them in a unique .root file (don't do that all at once. Merge 1000 files at a time, then merge all those files). The path to the merged root file needs to go in the header file, while the .C file needs a list of good runs (which the DQM experts should have provided to you).

In case you forgot how to run ROOT macros:
root Y_Z_calibration_mon_2_to_5.C
Y_Z_calibration_mon_2_to_5.C macro
macro.Loop()