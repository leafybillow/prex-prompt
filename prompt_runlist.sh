#! /bin/sh

while IFS= read -r line; do
    runnum=$line;
    ./prompt.sh $runnum;
done < $1
