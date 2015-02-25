#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include "rdtscp_timer/timing.hh"
#include "support.hh"

const static double FRAG_OCC = .05;
const static int TIMEOUT = 120;

static void fragment() {
	// constants
	const unsigned long long MEM_SIZE = get_total_memory();
	const unsigned long long MAX_ALLOC_SIZE = MEM_SIZE / 10000;

	std::vector<char*> allocations;							// hold our mallocs
	std::unordered_map<char*,int> allocSizes;		// hold our malloc sizes
	unsigned long long memFootprint = 0;				// total B of memory malloc'ed

	// start the clock
	std::clock_t start;
	start = std::clock();

	// run for 60 seconds
	while ( (std::clock() - start) / (double) CLOCKS_PER_SEC < TIMEOUT) {
		assert(allocations.size() == allocSizes.size());

		// make some new allocations
		for (int i = 0; i < 10; i++) {
			unsigned int size = rand() % MAX_ALLOC_SIZE;
			//char *a = new char[size];
			char *a = static_cast<char*>(malloc(size * sizeof(char)) );
			memset(a, rand(), size); // make sure we actually have pages allocated
			allocations.push_back(a);
			allocSizes[a] = size;
			memFootprint += size;
		}

		// free some old allocations; the key here is to
		// only free multiple allocations if we already have a lot
		while ((double) memFootprint / MEM_SIZE > FRAG_OCC) {
			int idx = rand() % allocations.size();
			char *victim = allocations[idx];
			memFootprint -= allocSizes[victim];
			allocSizes.erase(victim);

			//delete [] victim;
			free(victim);
			allocations.erase(allocations.begin() + idx);
		}
	}

	while (true)
		sleep(100000); 

	// Note: this will never execute because I'm too lazy to come up with a better
	//			 synchronization scheme between the allocation tester and the fragmenters
	for (int i = 0; i < allocations.size(); i++) {
		char *victim = allocations[i];
		delete [] victim;
		free(victim);
	}
}

int main(int argc, char **argv) {
	fragment();

	return 0;
}
