#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include "rdtscp_timer/timing.hh"

#define MB 1048576

using namespace std;

// Time the allocations of various sizes
static void testAllocation(double clock_speed_ghz) {
	vector<double> times;
	vector<double> sizes_bytes;
	vector<char*> ptrs;
	Timer t(clock_speed_ghz);
	
	const int N_ALLOCS = 1;
	const int N_TRIALS = 1000;

	for (int s = 0; s < N_ALLOCS; s++) {
		for (int i = 0; i < N_TRIALS; i++) {
			void *vptr = NULL;
			char *a = NULL;
			t.tick();
			assert(!posix_memalign(static_cast<void**>(&vptr), 2*MB, 2*MB));
			memset(vptr, rand(), 2*MB); // make sure we actually have pages allocated
			t.tock();
			assert(!(reinterpret_cast<unsigned long long>(a) & 0xFFFFF));
			times.push_back(t.get_time());
			ptrs.push_back(a);
		}

		while (true) {}
		for (int i = 0; i < N_TRIALS - 1; i++)
			cout << times[i] << ", ";
		cout << times[N_TRIALS - 1] << endl;

		//for (int i = 0; i < ptrs.size(); i++)
			//delete [] ptrs[i];

		ptrs.clear();
		times.clear();
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "WARNING: No system clock speed provided, RDTSCP timing will not be used!" << endl;
		testAllocation(-1);
	} else {
		testAllocation(atof(argv[1]));
	}

	return 0;
}
