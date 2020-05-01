#!/bin/sh
TIMEFORMAT=%R

#Delete previous record
echo "Clearing log file"
echo "" > record.txt

echo "Generating inputs"
# Generate all inputs
./generator # undo this comment if you want a new input
echo "Done generating inputs"

echo "Compiling the programs"
g++ -Wl,-stack_size,0x10000000000 -O -std=c++17 emst_ktree.cpp -o emst_ktree
g++ -Wl,-stack_size,0x10000000000 -O -std=c++17 geomst2.cpp -o geomst2
g++ -Wl,-stack_size,0x10000000000 -O -std=c++17 dualboruvka.cpp -o dualboruvka

for i in {0..29} 
do
	echo "Working on test case ${i}"
	(time ./emst_ktree < input${i}.txt > output.txt) 2>> record.txt

	# if [ $i -lt 39 ]
	# then
	(time ./geomst2 < input${i}.txt > output.txt) 2>> record.txt
	(time ./dualboruvka < input${i}.txt > output.txt) 2>> record.txt
	# fi
	echo "" >> record.txt
done

