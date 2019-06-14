#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    timenow=$(date +"%Y-%m%d-%H%M");
    mkdir ./summary/run$runnum;
    ./qwparity -r $runnum -c prex_respin2.conf \
	 --QwLog.logfile ./summary/run$runnum/run$runnum\_QwLog_$timenow.txt ;
    cp ./japanOutput/summary_$runnum.txt ./summary/run$runnum/;
    mv ./japanOutput/summary_$runnum.txt ./japanOutput/summary_$runnum\_respin2.txt;
done < $1
