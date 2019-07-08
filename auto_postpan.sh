#! /bin/sh
runnum=$1;
./redana -f ./rootfiles/prexTest_$runnum.000.root -c conf/combo_reg.conf
root -b -q '../postpan/scripts/GetBeamNoise.C('$runnum',"prexTest")'
mv prexTest_run$runnum\_postpan_summary.txt ./results

