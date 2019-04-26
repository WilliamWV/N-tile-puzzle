#!/bin/bash
puzzle8="test/8puzzle_instances.txt"
outputFile="idastar.csv"
tempFile="temp"
> $outputFile
make >> $tempFile
while IFS= read var
do
	./main -idastar $var >> $outputFile
done < "$puzzle8"

rm -rf $tempFile