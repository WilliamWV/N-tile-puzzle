#!/bin/bash
puzzle15="test/15puzzle_instances.txt"
outputFile="astar15.csv"
tempFile="temp"

> $outputFile
make >> $tempFile

ulimit -t 30

while IFS= read var
do
	./main -astar $var >> $outputFile
	rc=$?; if [[ $rc -ne 0 ]]; then echo -e "-,-,-,-,-" >> $outputFile; fi
	
done < "$puzzle15"

rm -rf $tempFile
