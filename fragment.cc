#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "rdtscp_timer/timing.hh"

#define MEM_SIZE 32934960000
#define MAX_ALLOC_SIZE (MEM_SIZE / 10000)
#define FRAG_OCC .05

static void fragment() {
  std::vector<char*> allocations;
  std::unordered_map<char*,int> allocSizes;
  unsigned long long memFootprint = 0;

  while (true) {
    assert(allocations.size() == allocSizes.size());

    // make some new allocations
    for (int i = 0; i < 10; i++) {
      unsigned int size = rand() % MAX_ALLOC_SIZE;
      //char *a = new char[size];
      char *a = static_cast<char*>(malloc(size * sizeof(char)) );
      memset(a, rand(), sizeof(a)); // make sure we actually have pages allocated
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

  for (int i = 0; i < allocations.size(); i++) {
    char *victim = allocations[i];
    //delete [] victim;
    free(victim);
  }
}

int main(int argc, char **argv) {
  fragment();

  return 0;
}
