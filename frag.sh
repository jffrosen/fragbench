#!/bin/bash

echo "No fragmentation allocation times:"
./testalloc > noFragTimes.txt

for run in {1..18}
do
  ./fragment &
done

sleep 60

echo "With fragmentation allocation times:"
./testalloc > fragTimes.txt

killall fragment
