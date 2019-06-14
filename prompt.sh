#! /bin/sh

runnum=$1;
if [ ! -d ./hallaweb_online/summary/run$runnum]; then
    mkdir ./hallaweb_online/summary/run$runnum;
fi

./qwparity -r $runnum -c prex_respin2.conf ;

./qwparity -r $runnum -c prex_respin2.conf \
    --rootfile-stem prexRespin2_pass2_ ;

root -b -q -l './rootMacros/PlotSummary.C('$runnum')';
cp ./japanOutput/summary_$runnum.txt ./japanOutput/summary_$runnum\_respin2.txt;

chgrp -R a-parity ./hallaweb_online/summary/run$runnum;
chmod -R 755 ./hallaweb_online/summary/run$runnum;
    
