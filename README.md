The dependency list goes as follows:
Bad channel list -> Misconfigured ASICS database -> DQM trees -> Good runs list -> dQ/dX

ASICS: Dependent on populated bad channel databases and the production of BNB_EXT anatrees (only one file per run is needed)
Good runs list: Dependent on the production of BNB + BNB_EXT DQM trees (produced with the correct ASICS)
dQ/dX: Dependent on the production of XYZcalibration trees.

Even though dQ/dX calibration depends on the good runs list, the DQM and XYZ calibration trees can be produced in parallel, but ASICS anatrees will have to be produced beforehand.
This implies the need for two campaigns:

Anatrees from limited BNB_EXT (1 file per run)
This needs BNB_EXT to be reconstructed on the fly and having the output dropped. Even better, Herb suggested to write a specific .fcl file which applies a minimal reconstruction only to get the minimum data products (signal processing) necessary to generate the 4 anatree branches that will be used by Mike’s script. Currently Brandon is integrating the bad channels in the database, as soon as that’s done, anatrees can be produced (anatrees depend on bad channel list because)
DQM trees and XYZ calibration trees on BNB_EXT + BNB
This will be a larger campaign that will need to run full reco on the swizzled file (but still dropping the output). DQM trees and XYZ calibration trees.
DQM trees will be used to generate good run list which will go as an input in Varuna’s dQ/dX script together with the XYZ calibration trees.

So, to start, head to ASICS and read the README file.