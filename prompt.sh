#! /bin/sh
runnum=$1;

if [ -z "$runnum" ]
then
    echo "Run Number is empty";
    exit 1;
fi

if [ -z "$2" ]
then
    eventrange=""
else
    eventrange="-e $2"
fi

#  Remove the LRB output files if they exist
shopt -s extglob
# find split file
slopefile_list=$(ls -1 ./LRBoutput/blueR$runnum*slope.root);
shopt -u extglob

for slopefile in $slopefile_list
do
    echo "deleting "  $slopefile;
    rm -f $slopefile;
done

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    $eventrange \
    --rootfile-stem prexTest_ 

# cp ./japanOutput/summary_$runnum.txt \
#     ./SummaryText/summary_prompt_pass1_$runnum.txt;

# Postpan regression to the first pass results
./auto_postpan.sh $runnum;

#JAPAN Second Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    $eventrange \
    --rootfile-stem prexTest_ \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_promptTest_$timenow.txt ;

# Make Summary Plots/Text and sync to HallA onlineWeb
./summary.sh $runnum;
    
