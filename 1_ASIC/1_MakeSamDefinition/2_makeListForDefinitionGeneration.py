import os, sys, json, pickle
import pandas as pd
from collections import OrderedDict as OD



runLim_low=15000
runLim_hi=20000

print "Making list of one file per run for runs in range between  {0} and run {1}".format(runLim_low,runLim_hi)
# Open file with filename list
print "Opening file with filename list"
fIn = 'list_allFiles_forrun3p2.list'
with open(fIn,'rb') as fileIn:
    lines = fileIn.read().split('\n')
# Retrieve name, run and subrun info from string
print "Retrieving name, run and subrun info from string"
name = []
run = []
subrun = []
for line in lines:
    if line:
        name.append(line)
        run .append(line.split('-')[2])
        subrun.append(line.split('-')[3].split('_')[0])
# Create dataframe with information
print "Creating dataframe with information"
data = OD([
        ('run', run),
        ('subrun', subrun),
        ('name', name),
    ])

df = pd.DataFrame(data)
# Sort dataframe
odf = df.sort_values(['run', 'subrun'])

# Find filenames with unique subrun per run
name = []
run = []
subrun = []
uniqueRun = 0
which_run = 0
for i,row in odf.iterrows():
    c_run = row['run']
    c_subrun = row['subrun']
    c_name = row['name']
    
    if uniqueRun != c_run:
        which_run=which_run+1
        if which_run==1:
            which_run=0
            uniqueRun = c_run
            run.append(c_run)
            subrun.append(c_subrun)
            name.append(c_name)
# Save data to dataframe
seldata = OD([
        ('run', run),
        ('subrun', subrun),
        ('name', name),
    ])
seldf = pd.DataFrame(seldata)

#convert strings to ints
seldf["run"]=pd.to_numeric(seldf["run"])
seldf["subrun"]=pd.to_numeric(seldf["subrun"])

#impose run limits


seldf= seldf[seldf["run"]>runLim_low]

seldf= seldf[seldf["run"]<runLim_hi]
#print seldf.head()
# Create list of filenames from unique definition
selList = [filename for filename in seldf['name']]

fileName = "list_1FilePerRun_firstfile_forrun3p2.list"
with open(fileName,'wb') as fileOut:
  fileOut.write("file_name ")
  for fileName in selList[:-1]:
    fileOut.write("%s, " %(fileName))
  fileOut.write(selList[-1])
fileOut.close()
