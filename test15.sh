#!/bin/bash
puzzle15="test/15puzzle_instances.txt"
outputFile="out15.txt"
tempFile="temp"

> $outputFile
make >> $tempFile

ulimit -t 30

echo -e "15-Puzzle Instances:\n\n" >> $outputFile

i=1
echo -e "A*:\n" >> $outputFile
while IFS= read var
do
	echo -e $i>>$outputFile
	./main -astar $var >> $outputFile
	rc=$?; if [[ $rc -ne 0 ]]; then echo -e "Failed" >> $outputFile; fi
	i=$((i+1))

done < "$puzzle15"

rm -rf $tempFile
