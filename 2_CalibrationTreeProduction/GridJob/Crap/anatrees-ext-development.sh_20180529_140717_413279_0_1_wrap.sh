#!/bin/sh
#
umask 002
# /fife/local/scratch/uploads/uboone/sporzio/2018-05-29_140715.587231_9786/anatrees-ext-development.sh_20180529_140717_413279_0_1_wrap.sh
# Automatically generated by: 
#          jobsub -e JOBSUBJOBSECTION --lines +JobsubJobSection="6" -n -n --group=uboone -f /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC --OS=SL6 --expected-lifetime=long --append_condor_requirements=(TARGET.HAS_CVMFS_uboone_opensciencegrid_org==true) -l +JobsubParentJobId="$(DAGManJobId)@jobsub01.fnal.gov" -l +JobsubJobId="$(CLUSTER).$(PROCESS)@jobsub01.fnal.gov" -l +Owner="sporzio" -e JOBSUBPARENTJOBID -l +JobsubServerVersion="1.2.6.2.1" -l +JobsubClientVersion="1.2.5" -l +JobsubClientDN="/DC=org/DC=cilogon/C=US/O=Fermi National Accelerator Laboratory/OU=People/CN=Salvatore davide Porzio/CN=UID:sporzio" -l +JobsubClientIpAddress="131.225.240.146" -l +JobsubClientKerberosPrincipal="sporzio@FNAL.GOV" ./anatrees-ext-development.sh --nfile 1 --group uboone -g -c wrapper.fcl --ups uboonecode -r development -b debug --localtar /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar --workdir /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees --outdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees --logdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees --sam_defname sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles --sam_project sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707 -n 1000000 --end-script ./merge_dqm_hists.sh --init /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh --validate --declare --maintain_parentage --process 4 


set_jobsub_debug(){
    export PS4='$LINENO:'
    set -xv
}
[[ "$JOBSUB_DEBUG" ]] && set_jobsub_debug



cleanup_condor_dirs(){
if [[ -d "$_CONDOR_JOB_IWD" ]]; then
   find $_CONDOR_JOB_IWD -mindepth 1 -maxdepth 1 -type d -exec rm -rf {} \;
fi
}


is_set() {
  [ "$1" != "" ]
  RSLT=$?
  return $RSLT
}

get_log_sizes() {
    total=$JOBSUB_MAX_JOBLOG_SIZE
    head=$JOBSUB_MAX_JOBLOG_HEAD_SIZE
    tail=$JOBSUB_MAX_JOBLOG_TAIL_SIZE

    if (( is_set $head) && ( is_set $tail )); then
         total=$(($head + $tail))
    elif ( is_set $total ); then
            if ((  is_set $head ) && (($total > $head))); then
                tail=$(($total - $head))
                total=$((head + tail))
            elif ((  is_set $tail ) && (($total > $tail))); then
                head=$(($total - $tail))
                total=$((head + tail))
            else
                head=$(( $total / 5 ))
                tail=$(( 4 * $total / 5))
            fi
    else
        total=5000000
        head=1000000
        tail=4000000
    fi
    export JOBSUB_MAX_JOBLOG_SIZE=$total
    export JOBSUB_MAX_JOBLOG_HEAD_SIZE=$head
    export JOBSUB_MAX_JOBLOG_TAIL_SIZE=$tail

}

jobsub_truncate() {
    get_log_sizes
    JOBSUB_LOG_SIZE=`wc -c $1 | awk '{print $1}'`
    if ( ! is_set $JSB_TMP );then
            export JSB_TMP=/tmp/$$
        mkdir -p $JSB_TMP
    fi
    JSB_OUT=$JSB_TMP/truncated
    if [ $JOBSUB_LOG_SIZE -gt $JOBSUB_MAX_JOBLOG_SIZE ]; then
        head -c $JOBSUB_MAX_JOBLOG_HEAD_SIZE $1 > $JSB_OUT
        echo "
jobsub:---- truncated after $JOBSUB_MAX_JOBLOG_HEAD_SIZE bytes--
" >>$JSB_OUT
        echo "
jobsub:---- resumed for last $JOBSUB_MAX_JOBLOG_TAIL_SIZE bytes--
" >>$JSB_OUT
        tail -c $JOBSUB_MAX_JOBLOG_TAIL_SIZE $1 >> $JSB_OUT
    else
        cp $1 $JSB_OUT
    fi
    cat $JSB_OUT
    rm $JSB_OUT
}


redirect_output_start(){
    exec 7>&1
    exec >${JSB_TMP}/JOBSUB_LOG_FILE
    exec 8>&2
    exec 2>${JSB_TMP}/JOBSUB_ERR_FILE
}

redirect_output_finish(){
    exec 1>&7 7>&-
    exec 2>&8 8>&-
    jobsub_truncate ${JSB_TMP}/JOBSUB_ERR_FILE 1>&2
    jobsub_truncate ${JSB_TMP}/JOBSUB_LOG_FILE
}


normal_exit(){
    redirect_output_finish
    cleanup_condor_dirs
}

signal_exit(){
    echo "$@ "
    echo "$@ " 1>&2
    exit 255
}


trap normal_exit EXIT
trap "signal_exit received signal TERM"  TERM
trap "signal_exit received signal KILL" KILL
trap "signal_exit received signal ABRT" ABRT
trap "signal_exit received signal QUIT" QUIT
trap "signal_exit received signal ALRM" ALRM
trap "signal_exit received signal INT" INT
trap "signal_exit received signal BUS" BUS
trap "signal_exit received signal PIPE" PIPE

        

setup_ifdh_env(){
#
# create ifdh.sh which runs
# ifdh in a seperate environment to
# keep it from interfering with users ifdh set up
#
cat << '_HEREDOC_' > ${JSB_TMP}/ifdh.sh
#!/bin/sh
#
which ifdh > /dev/null 2>&1
has_ifdh=$?
if [ "$has_ifdh" -ne "0" ] ; then
    unset PRODUCTS
    for setup_file in /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setups /grid/fermiapp/products/common/etc/setups.sh /fnal/ups/etc/setups.sh ; do
      if [ -e "$setup_file" ] && [ "$has_ifdh" -ne "0" ]; then
         source $setup_file
         ups exist ifdhc $IFDH_VERSION
         has_ifdh=$?
         if [ "$has_ifdh" = "0" ] ; then
             setup ifdhc $IFDH_VERSION
             break
         else
            unset PRODUCTS
         fi
     fi
   done
fi
which ifdh > /dev/null 2>&1
if [ "$?" -ne "0" ] ; then
    echo "Can not find ifdh version $IFDH_VERSION ,exiting!"
    echo "Can not find ifdh version $IFDH_VERSION ,exiting! ">&2
    exit 1
else
    ifdh "$@"
    exit $?
fi
_HEREDOC_
chmod +x ${JSB_TMP}/ifdh.sh
}
            

#############################################################
# main ()                                                     #
###############################################################
touch .empty_file
# Hold and clear arg list
args="$@"
set - ""
[[ "$JOBSUB_DEBUG" ]] && set_jobsub_debug

export JSB_TMP=$_CONDOR_SCRATCH_DIR/jsb_tmp
mkdir -p $JSB_TMP
export _CONDOR_SCRATCH_DIR=$_CONDOR_SCRATCH_DIR/no_xfer
export TMP=$_CONDOR_SCRATCH_DIR
export TEMP=$_CONDOR_SCRATCH_DIR
export TMPDIR=$_CONDOR_SCRATCH_DIR
mkdir -p $_CONDOR_SCRATCH_DIR
redirect_output_start


setup_ifdh_env
export PATH="${PATH}:."

export CONDOR_DIR_INPUT=${_CONDOR_SCRATCH_DIR}/${PROCESS}/TRANSFERRED_INPUT_FILES
mkdir -p ${_CONDOR_SCRATCH_DIR}/${PROCESS}
mkdir -p ${CONDOR_DIR_INPUT}
echo `date` BEGIN WRAPFILE COPY-IN ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/
>&2 echo `date` BEGIN WRAPFILE COPY-IN ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/
${JSB_TMP}/ifdh.sh  log "sporzio BEGIN ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/"
${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/
${JSB_TMP}/ifdh.sh  log "sporzio FINISHED ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/"
echo `date` FINISHED WRAPFILE COPY-IN ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/
>&2 echo `date` FINISHED WRAPFILE COPY-IN ${JSB_TMP}/ifdh.sh  cp  -D    /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees/work7571e840a3536fa12b6fe00eaea916af.tar ${CONDOR_DIR_INPUT}/

export JOBSUB_EXE_SCRIPT=`find . -name anatrees-ext-development.sh -print`
chmod +x $JOBSUB_EXE_SCRIPT
${JSB_TMP}/ifdh.sh log "sporzio:BEGIN EXECUTION $JOBSUB_EXE_SCRIPT  --nfile 1 --group uboone -g -c wrapper.fcl --ups uboonecode -r development -b debug --localtar /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar --workdir /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees --outdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees --logdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees --sam_defname sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles --sam_project sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707 -n 1000000 --end-script ./merge_dqm_hists.sh --init /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh --validate --declare --maintain_parentage --process 4  
 "


export NODE_NAME=`hostname`
export BOGOMIPS=`grep bogomips /proc/cpuinfo | tail -1 | cut -d ' ' -f2`
export VENDOR_ID=`grep vendor_id /proc/cpuinfo | tail -1 | cut -d ' ' -f2`
export poms_data='{"campaign_id":"'$CAMPAIGN_ID'","task_definition_id":"'$TASK_DEFINITION_ID'","task_id":"'$POMS_TASK_ID'","job_id":"'$POMS_JOB_ID'","batch_id":"'$JOBSUBJOBID'","host_site":"'$HOST_SITE'","bogomips":"'$BOGOMIPS'","node_name":"'$NODE_NAME'","vendor_id":"'$VENDOR_ID'"}'

        
${JSB_TMP}/ifdh.sh log poms_data=$poms_data
echo `date` BEGIN EXECUTION $JOBSUB_EXE_SCRIPT  --nfile 1 --group uboone -g -c wrapper.fcl --ups uboonecode -r development -b debug --localtar /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar --workdir /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees --outdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees --logdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees --sam_defname sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles --sam_project sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707 -n 1000000 --end-script ./merge_dqm_hists.sh --init /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh --validate --declare --maintain_parentage --process 4  
>&2 echo `date` BEGIN EXECUTION $JOBSUB_EXE_SCRIPT  --nfile 1 --group uboone -g -c wrapper.fcl --ups uboonecode -r development -b debug --localtar /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar --workdir /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees --outdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees --logdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees --sam_defname sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles --sam_project sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707 -n 1000000 --end-script ./merge_dqm_hists.sh --init /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh --validate --declare --maintain_parentage --process 4  
$JOBSUB_EXE_SCRIPT --nfile 1 --group uboone -g -c wrapper.fcl --ups uboonecode -r development -b debug --localtar /pnfs/uboone/resilient/users/sporzio/GridFiles/uboonecode_v06_26_01_17.tar --workdir /pnfs/uboone/scratch/users/sporzio/Work/DqmCalibrationNtuples/ext/v1/anatrees --outdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Samples/anatrees --logdir /pnfs/uboone/scratch/users/sporzio/DqmCalibrationNtuples/ext/v1/Logs/anatrees --sam_defname sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles --sam_project sporzio_prod_extbnb_swizzle_inclusive_v5_17-05-18_1kfiles_20180529140707 -n 1000000 --end-script ./merge_dqm_hists.sh --init /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh --validate --declare --maintain_parentage --process 4   
JOB_RET_STATUS=$?
echo `date` $JOBSUB_EXE_SCRIPT COMPLETED with exit status $JOB_RET_STATUS
echo `date` $JOBSUB_EXE_SCRIPT COMPLETED with exit status $JOB_RET_STATUS 1>&2
${JSB_TMP}/ifdh.sh log "sporzio:anatrees-ext-development.sh COMPLETED with return code $JOB_RET_STATUS" 
exit $JOB_RET_STATUS
