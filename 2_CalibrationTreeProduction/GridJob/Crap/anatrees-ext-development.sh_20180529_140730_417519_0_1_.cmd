universe          = vanilla
executable        = /fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786/anatrees-ext-development.sh_20180529_140730_417519_0_1_wrap.sh
arguments         =  --nfile  1  --group  uboone  -g  -c  wrapper.fcl  --ups  uboonecode  -r  development  -b  debug  --localtar  /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar  --workdir  /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees  --outdir  /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees  --logdir  /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees  --sam_defname  sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles  --sam_project  sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707  -n  1000000  --end-script  ./merge_dqm_hists.sh  --init  /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh  --validate  --declare  --maintain_parentage  --process  44 
output                = /fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786/anatrees-ext-development.sh_20180529_140730_417519_0_1_cluster.$(Cluster).$(Process).out
error                 = /fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786/anatrees-ext-development.sh_20180529_140730_417519_0_1_cluster.$(Cluster).$(Process).err
log                   = /fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786/anatrees-ext-development.sh_20180529_140730_417519_0_1_.log
environment   = CLUSTER=$(Cluster);PROCESS=$(Process);CONDOR_TMP=/fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786;CONDOR_EXEC=/tmp;DAGMANJOBID=$(DAGManJobId);JOBSUBJOBSECTION=46;JOBSUBPARENTJOBID=$(DAGManJobId)@jobsub01.fnal.gov;GRID_USER=sporzio;IFDH_BASE_URI=http://samweb.fnal.gov:8480/sam/uboone/api;JOBSUBJOBID=$(CLUSTER).$(PROCESS)@jobsub01.fnal.gov;EXPERIMENT=uboone
rank                  = Mips / 2 + Memory
job_lease_duration = 3600
notification = Never
when_to_transfer_output = ON_EXIT_OR_EVICT
transfer_output                 = True
transfer_output_files = .empty_file
transfer_error                  = True
transfer_executable         = True
transfer_input_files = ./anatrees-ext-development.sh
+JobsubJobSection="46"
+JobsubParentJobId="$(DAGManJobId)@jobsub01.fnal.gov"
+JobsubJobId="$(CLUSTER).$(PROCESS)@jobsub01.fnal.gov"
+Owner="sporzio"
+JobsubServerVersion="1.2.6.2.1"
+JobsubClientVersion="1.2.5"
+JobsubClientDN="/DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=Salvatore davide Porzio/CN=UID:sporzio"
+JobsubClientIpAddress="131.225.240.146"
+JobsubClientKerberosPrincipal="sporzio@FNAL.GOV"
+JOB_EXPECTED_MAX_LIFETIME = 85200
+PNFS_INPUT_FILES = "/pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar" 
notify_user = sporzio@fnal.gov
x509userproxy = /var/lib/jobsub/creds/proxies/uboone/x509cc_sporzio_Analysis
+RunOnGrid                          = True
+AccountingGroup = "group_uboone.sporzio"
+Jobsub_Group="uboone"
+DesiredOS ="SL6"
+Drain = False
+GeneratedBy ="NO_UPS_VERSION jobsub01.fnal.gov"
+DESIRED_usage_model = "DEDICATED,OPPORTUNISTIC"
requirements  = target.machine =!= MachineAttrMachine1 && target.machine =!= MachineAttrMachine2  && ( DesiredOS =?= NULL || stringlistimember(Target.IFOS_installed,DesiredOS)) && (stringListsIntersect(toUpper(target.HAS_usage_model), toUpper(my.DESIRED_usage_model))) && (TARGET.HAS_CVMFS_uboone_opensciencegrid_org==true) 


queue 1