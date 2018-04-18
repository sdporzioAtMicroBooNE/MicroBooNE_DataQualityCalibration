import samweb_client as swc

# Settings
defName = "sporzio_run3_oneFilePerRun_18-04-17"

# Open file
fIn = "list_1FilePerRun.list"
with open(fIn,'rb') as fileIn:
	fileList = fileIn.read()

# Create definition
samweb = swc.SAMWebClient(experiment='uboone')
samweb.createDefinition(defName, fileList, user="sporzio", group="uboone", description="Run 3, one file per each run")
print "Created definition %s" %(defName)