#! /bin/sh
runnum=$1;

#JAPAN First Pass
timenow=$(date +"%Y-%m%d-%H%M");
./qwparity -r $runnum -c prex.conf \
    --QwLog.logfile ./QwLog/QwLog_run$runnum\_prompt_pass1_$timenow.txt ;

#JAPAN Second Pass
timenow=$(date +"%Y-%m%d-%H%M");
./qwparity -r $runnum -c prex.conf \
    --rootfile-stem prexPrompt_pass2_ \
    --QwLog.logfile ./QwLog/QwLog_run$runnum\_prompt_pass2_$timenow.txt ;

# Beam Modulation Data Extraction
./summary.sh $runnum;
    
