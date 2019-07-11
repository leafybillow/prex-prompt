#! /bin/sh
runnum=$1;

if [ -z "$runnum" ] 
then
    echo "Run Number is empty";
    exit 1;
fi    

level="Test"
shopt -s extglob
# find split file
rootfile_list=$(ls -1 ./rootfiles/prex$level\_$runnum.!(*jlab.org*).root);
shopt -u extglob

for rootfile  in $rootfile_list
do
    trim=${rootfile%.root}
    run_dot_seg=${trim#*_}
    run_num=${run_dot_seg%.*}
    run_seg=${run_dot_seg/./_}

    ./redana \
    	-f $rootfile \
    	-c ./conf/combo_reg.conf ;

    root -b -q '../postpan/scripts/GetBeamNoise.C("'$run_seg'","prexTest")'

    if [ ! -d ./hallaweb_online/width/run$run_seg ]; then
    	mkdir ./hallaweb_online/width/run$run_seg;
    fi

    cp  ./results/prexTest_$run_seg\_postpan_summary.txt \
    	./hallaweb_online/width/run$run_seg/;

done

