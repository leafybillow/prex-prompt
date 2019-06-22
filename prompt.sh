#! /bin/sh
runnum=$1;

#  Remove the LRB output files if they exist
if [ -f ./LRBoutput/blueR$runnum.000new.slope.root ]; then
    rm -f ./LRBoutput/blueR$runnum.000new.slope.root
fi

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass1_ \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

# cp ./japanOutput/summary_$runnum.txt \
#     ./SummaryText/summary_prompt_pass1_$runnum.txt;

#JAPAN Second Pass
timenow=$(date +"%Y-%m%d-%H%M");

./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass2_ \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass2_$timenow.txt ;


# BeamMod Data Extraction (FIXME)
# BeamMod Instant Slope Calculation (FIXME)
# BeamMod Instant correction and summary (FIXME)

# Make Summary Plots/Text and sync to HallA onlineWeb
./summary.sh $runnum;
    
