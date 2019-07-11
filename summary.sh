#!/bin/sh

runnum=$1
level="Test"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./rootfiles/prex$level\_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    # strip out [run.seg]

    trim=${rootfile%.root}
    run_dot_seg=${trim#*_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    if [ ! -d ./SummaryPlots/run$run_seg ]; then
	mkdir ./SummaryPlots/run$run_seg;
    fi

    root -b -q -l './rootMacros/PlotSummary.C("'$rootfile'")';

    if [ ! -d ./hallaweb_online/width/run$run_seg ]; then
    	mkdir ./hallaweb_online/width/run$run_seg;
    fi

    cp  ./SummaryPlots/run$run_seg/* \
    	./hallaweb_online/width/run$run_seg/;

    # cp ./japanOutput/summary_*$runnum*.txt \
    # 	./SummaryText/

    # mv  ./SummaryText/summary_$run_num.txt \
    # 	./SummaryText/summary_$level_$run_seg.txt \

    # cp  ./SummaryText/summary_$level_$run_seg.txt \
    # 	./hallaweb_online/summary/run$run_seg/ ;

    # #Change user group and permission
    # chgrp -R a-parity ./hallaweb_online/summary/run$run_seg;
    # chmod -R 755 ./hallaweb_online/summary/run$run_seg;    

done


