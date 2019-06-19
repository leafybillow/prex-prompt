#! /bin/sh

while IFS= read -r line; do
    runnum=$line
    ./summary.sh $runnum;
done < $1


