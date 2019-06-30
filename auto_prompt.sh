#!/bin/bash

# auto prompt analysis script for PREX2
# To start with a particular run number.
# ./auto_prompt.sh <run_num>
# if not it will start from the latest coda run

# re-analyze run?
# 1=Yes (overwrite), 0=No (skip the run)
reanalyze=0
waittime=0

# minimum time passed since last data writing
# set to 5min
min_time_passed=300

#JAPAN_OUTPUT_DIR=$QW_ROOTFILES
#DATA_DIR=$QW_DATA
JAPAN_OUTPUT_DIR=/chafs2/work1/apar/japanOutput
DATA_DIR=/adaq1/data1/apar/

# Get Current Run Number
rcnum=`cat ~apar/datafile/rcRunNumber`

if [[ $# -eq 0 ]]; then
    echo "Start with the current run $rcnum"
    thisrun=$rcnum
else
    thisrun=$1
    reanalyze=$2
fi

if ((thisrun>rcnum)); then
    echo "$thisrun has not been taken yet"
    exit 1
fi

while [ $thisrun -le $rcnum ]; do
    if [ $thisrun -lt $rcnum ]; then
	if [[ $(find $JAPAN_OUTPUT_DIR -type f -iname "*rompt*$thisrun*" 2> /dev/null) ]]; then
	    if [[ $reanalyze -eq 1 ]]; then
		echo "Launch replay for $thisrun"
		./prompt.sh $thisrun
	    else
		echo "japan output root file already created... skip this run $thisrun"
	    fi
	else	    
	    echo "Launch replay for $thisrun"
	    ./prompt.sh $thisrun
	fi
	waittime=0
	thisrun=$((thisrun + 1))
    else
	# Now time
	nowtime=`date +%s`

	# Get modified time for the lastest data file
	last_coda_file=`ls -t $DATA_DIR/*$rcnum*.dat* | head -1`
	time_modified=`date -r $last_coda_file +%s`

	timediff=$((nowtime-time_modified))
	if ((timediff > min_time_passed)); then
	    # Consider the run has been finished already
	    # Check if there is root file created
	    if [[ $(find $JAPAN_OUTPUT_DIR -type f -iname "*rompt*$thisrun*" 2> /dev/null) ]]; then
		echo "====The last run analysis already launched===="
	    else
		echo "Launch replay for $thisrun"
		./prompt.sh $thisrun
	    fi

	    waittime=0

	    rcnum=`cat ~apar/datafile/rcRunNumber`
	    # add another loop (up to 24h) to check if there has been a new run started
	    while [ $thisrun -eq $rcnum ]; do
		echo "====Wait for 10m for a new run, $waittime===="
		# no new run since then?
		sleep 10m #wait for 10 minutes
		rcnum=`cat ~apar/datafile/rcRunNumber`
		
		waittime=$((waittime + 1))
		if [ $waittime -gt 144 ]; then
		    echo "====no new datafile in the past 24 hours, STOP========"
		    exit
		fi
	    done
	    thisrun=$((thisrun + 1))
	else
	    echo "====It seems the run is ongoing... check again 10 min later===="
	    sleep 10m 
	fi
    fi

    rcnum=`cat ~apar/datafile/rcRunNumber`
    
done
