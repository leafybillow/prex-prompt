#! /bin/sh
runnum=$1;

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");
./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass1_ \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

cp ./japanOutput/summary_$runnum.txt \
    ./SummaryText/summary_prompt_pass1_$runnum.txt;

#JAPAN Second Pass
timenow=$(date +"%Y-%m%d-%H%M");
./qwparity -r $runnum -c prex_prompt.conf \
    --rootfile-stem prexPrompt_pass2_ \
    --QwLog.logfile ./LogFiles/QwLog_run$runnum\_prompt_pass2_$timenow.txt ;

# *Assumming prompt summary gets updated at 2nd pass.
cp ./japanOutput/summary_$runnum.txt \
    ./SummaryText/summary_prompt_$runnum.txt;

# BeamMod Data Extraction (FIXME)

# Make Summary Plots/Text and Rsyncs to HallA onlineWeb
./summary.sh $runnum;
    
