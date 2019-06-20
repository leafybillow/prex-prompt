#! /bin/sh

runnum=$1;

# Making Summary Plots
if [ ! -d ./SummaryPlots/run$runnum ]; then
    mkdir ./SummaryPlots/run$runnum;
fi
root -b -q -l './rootMacros/PlotSummary.C('$runnum')';

#Rsync to OnlineWeb folder
if [ ! -d ./hallaweb_online/summary/run$runnum ]; then
    mkdir ./hallaweb_online/summary/run$runnum;
fi
rsync -a ./SummaryPlots/run$runnum/
    ./hallaweb_online/summary/run$runnum  ;

#Change user group and permission
chgrp -R a-parity ./hallaweb_online/summary/run$runnum;
chmod -R 755 ./hallaweb_online/summary/run$runnum;
    
