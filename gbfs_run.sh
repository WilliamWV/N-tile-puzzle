puzzle8="test/8puzzle_instances.txt"
outputFile="gbfs.csv"
tempFile="temp"
> $outputFile
make >> $tempFile
while IFS= read var
do
	./main -gbfs $var >> $outputFile
done < "$puzzle8"

rm -rf $tempFile