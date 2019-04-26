#!/bin/bash
puzzle8="test/8puzzle_instances.txt"
outputFile="out8.txt"
tempFile="temp"

> $outputFile

make >> $tempFile

echo -e "8-Puzzle Instances:\n\n" >> $outputFile

echo -e "BFS:\n" >> $outputFile
while IFS= read var
do
	./main -bfs $var >> $outputFile
done < "$puzzle8"

echo -e "A*:\n" >> $outputFile
while IFS= read var
do
	./main -astar $var >> $outputFile
done < "$puzzle8"

echo -e "GBFS:\n" >> $outputFile
while IFS= read var
do
	./main -gbfs $var >> $outputFile
done < "$puzzle8"

echo -e "IDFS:\n" >> $outputFile
while IFS= read var
do
	./main -idfs $var >> $outputFile
done < "$puzzle8"

echo -e "IDA*:\n" >> $outputFile
while IFS= read var
do
	./main -idastar $var >> $outputFile
done < "$puzzle8"


rm -rf $tempFile

