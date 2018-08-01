First you'll need the bad channel database to be populated. This has been previously done by Jyoti and Brandon. Once that's done, you can produce anatrees for the ASIC studies.

# 1.
The ASIC studies takes as an input anatrees for the Run. One file per run should be enough and shouldn't create the need for a massive processing campaign. In order to get a definition for the run you are currently studying you'll want to use the files in the ASICS dir.

First put ALL the filenames from the current run in a text file (just run the first script). The python script is going to make some string manipulation and make sure you end up with a list of files, one only per run. Finally the pythonsamweb interface in script 3 is going to create the definition (the reason for all this mess is that bash has a limit on the number of characters in a command, which is why we have to bother with python).

# 2.
Create the anatrees.
standardAna_withReco1_outputDropped.fcl is a special fcl file that applies the reco1 stage for generating hits and generates the anatree but drops the output (which we don't need) in order not to waste resources.

# 3.
Use the anatrees as an input and take a look at the plots coming out of the root file. It's a Gallery file, make sure you have it properly set up. Some variables are hard-coded so take a look at the file first. In the output file you should be able to identify regions with misconfigured asics. M. Mooney has previously been in charge of this. You can take a look at his slides for guidance.
https://microboone-docdb.fnal.gov/cgi-bin/private/RetrieveFile?docid=7345&filename=MicroBooNE_AssortedSlides_17_03_03.pdf&version=1
