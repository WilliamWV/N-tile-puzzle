#!/bin/bash
puzzle8="test/8puzzle_instances.txt"
outputFile="astar8.csv"
tempFile="temp"
> $outputFile
make >> $tempFile
while IFS= read var
do
	./main -astar $var >> $outputFile
done < "$puzzle8"

rm -rf $tempFile