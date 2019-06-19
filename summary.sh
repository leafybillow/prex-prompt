#! /bin/sh

runnum=$1;

if [ ! -d ./summary/run$runnum]; then
    mkdir ./summary/run$runnum;
fi

root -b -q -l './rootMacros/PlotSummary.C('$runnum')';
cp ./japanOutput/summary_$runnum.txt \
    ./summary/run$runnum/summary_prompt_$runnum.txt;

if [ ! -d ./hallaweb_online/summary/run$runnum]; then
    mkdir ./hallaweb_online/summary/run$runnum;
fi

rsync -a ./summary/run$runnum/ --exclude *QwLog* \
    ./hallaweb_online/summary/run$runnum  ;

chgrp -R a-parity ./hallaweb_online/summary/run$runnum;
chmod -R 755 ./hallaweb_online/summary/run$runnum;
    
