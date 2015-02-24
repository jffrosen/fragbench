# fragbench
Memory Fragmentation/Malloc Benchmark

This benchmark fragments memory through a serious of random allocations and then
performs a series of aligned mallocs to test memory allocation performance under
fragmented conditions.

Dependencies:
https://github.com/jffrosen/rdtscp_timer

How to Run:
Build the benchmark using Make and run frag.sh

Notes:
May require tuning based on machine specifics
