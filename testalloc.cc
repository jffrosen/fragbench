#include <iostream>
#include <vector>
#include <cassert>
#include "rdtscp_timer/timing.hh"

#define MEM_SIZE 32934960000
#define CLOCK 2394178
#define MB 1048576

using namespace std;

// Time the allocations of various sizes
static void testAllocation() {
  vector<double> times;
  vector<double> sizes_bytes;
  vector<char*> ptrs;
  Timer t(CLOCK);
  
  const int N_ALLOCS = 1;
  const int N_TRIALS = 100000;
  const unsigned long long sizes[4] = {MEM_SIZE / 1000000, MEM_SIZE / 100000, MEM_SIZE / 10000, MEM_SIZE / 1000};

  for (int s = 0; s < N_ALLOCS; s++) {
    for (int i = 0; i < N_TRIALS; i++) {
      void *vptr = NULL;
      char *a = NULL;
      t.tick();
      //char *a = static_cast<char*>(malloc(sizes[s] * sizeof(char)) );
      assert(!posix_memalign(static_cast<void**>(&vptr), 2*MB, 2*MB));
      t.tock();
      a = static_cast<char*>(vptr);
      assert(!(reinterpret_cast<unsigned long long>(a) & 0xFFFFF));
      times.push_back(t.get_time());
      ptrs.push_back(a);
    }

    cout << "Alloc " << sizes[s] << "B, ";

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
  testAllocation();

  return 0;
}
