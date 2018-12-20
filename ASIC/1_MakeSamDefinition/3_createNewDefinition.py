import samweb_client as swc

# Settings
defName = "ogoodwin_run3p2_oneFilePerRun_thirdfile"

# Open file
fIn = "list_1FilePerRun_thirdfile_forrun3p2.list"
with open(fIn,'rb') as fileIn:
	fileList = fileIn.read()

# Create definition
samweb = swc.SAMWebClient(experiment='uboone')
samweb.createDefinition(defName, fileList, user="ogoodwin", group="uboone", description="Run 1, one file per each run")
print "Created definition %s" %(defName)
