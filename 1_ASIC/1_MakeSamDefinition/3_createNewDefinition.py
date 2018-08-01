import samweb_client as swc

# Settings
defName = "sporzio_run2_oneFilePerRun_27-04-18"

# Open file
fIn = "list_1FilePerRun.list"
with open(fIn,'rb') as fileIn:
	fileList = fileIn.read()

# Create definition
samweb = swc.SAMWebClient(experiment='uboone')
samweb.createDefinition(defName, fileList, user="sporzio", group="uboone", description="Run 2, one file per each run")
print "Created definition %s" %(defName)