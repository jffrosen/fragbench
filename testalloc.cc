#include <iostream>
#include <vector>
#include "rdtscp_timer/timing.hh"

#define MEM_SIZE 32934960000
#define CLOCK 2394178

using namespace std;

// Time the allocations of various sizes
static void testAllocation() {
  vector<double> times;
  vector<char*> ptrs;
  Timer t(CLOCK);
  
  //const int N_ALLOCS = 4;
  const int N_ALLOCS = 1;
  const int N_TRIALS = 100000;
  const unsigned long long sizes[4] = {MEM_SIZE / 1000000, MEM_SIZE / 100000, MEM_SIZE / 10000, MEM_SIZE / 1000};

  for (int s = 0; s < N_ALLOCS; s++) {
    for (int i = 0; i < N_TRIALS; i++) {
      t.tick();
      char *a = static_cast<char*>(malloc(sizes[s] * sizeof(char)) );
      t.tock();
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
