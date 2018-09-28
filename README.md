For more information, see the following documents:

Detector Calibration Public Note: https://microboone-docdb.fnal.gov/cgi-bin/private/RetrieveFile?docid=15584&filename=microboone-doc-15584-v13.pdf&version=13

Detector Calibration Internal Note: https://microboone-docdb.fnal.gov/cgi-bin/private/RetrieveFile?docid=14754&filename=calibration_technote_v3.pdf&version=3


The dependency list of prerequisites goes as follows:
Bad channel list -> Misconfigured ASICS database -> DQM trees -> Good runs list -> dQ/dX

ASICS: Dependent on populated bad channel databases and the production of BNB_EXT anatrees (only one file per run is needed)
Good runs list: Dependent on the production of BNB + BNB_EXT DQM trees (produced with the correct ASICS)
dQ/dX: Dependent on the production of XYZcalibration trees.

Even though dQ/dX calibration depends on the good runs list, the DQM and XYZ calibration trees can be produced in parallel, but ASICS anatrees will have to be produced beforehand.
This implies the need for two production campaigns:

- Anatrees from limited BNB_EXT (1 file per run)
This needs BNB_EXT to be reconstructed on the fly and having the output dropped. Even better, you can write a specific .fcl file which applies a minimal reconstruction only to get the minimum data products (signal processing) necessary to generate the 4 anatree branches that will be used by the ASIC's script. 

- DQM trees and XYZ calibration trees on BNB_EXT + BNB
This will be a larger campaign that will need to run full reco on the swizzled file (but still dropping the output).
DQM trees will be used to generate good run list which will go as an input in the dQ/dX script together with the XYZ calibration trees.

So, to start, head to ASICS and read the README file.
