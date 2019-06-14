#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    
    mkdir ./summary/run$runnum;
    ./qwparity -r $runnum -c prex_respin2.conf \
	--QwLog.logfile ./summary/run$runnum/run$runnum\_QwLog_pass1_$timenow.txt ;

    ./qwparity -r $runnum -c prex_respin2.conf \
    	--rootfile-stem prexRespin2_pass2_ \
    	--QwLog.logfile ./summary/run$runnum/run$runnum\_QwLog_pass2_$timenow.txt ;

    root -b -q -l './scripts/PlotSummary.C('$runnum')';
    cp ./japanOutput/summary_$runnum.txt ./summary/run$runnum/;
    mv ./japanOutput/summary_$runnum.txt ./japanOutput/summary_$runnum\_respin2.txt;
    
done < $1
