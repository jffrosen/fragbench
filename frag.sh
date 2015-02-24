#!/bin/bash

./testalloc > noFragTimes.txt

for run in {1..12}
do
	./fragment &
done

sleep 150

killall -SIGSTOP fragment
echo "Done fragmenting...."

./testalloc > fragTimes.txt

echo "No fragmentation allocation times:"
./parse_csv.py noFragTimes.txt
echo "With fragmentation allocation times:"
./parse_csv.py fragTimes.txt

killall fragment
