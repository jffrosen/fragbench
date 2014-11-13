#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <pthread.h>
#include <fcntl.h>
#include <malloc.h>
#include "rdtscp_timer/timing.hh"

#define MEM_SIZE 32934960000
#define MAX_ALLOC_SIZE (MEM_SIZE / 10000)
#define FRAG_OCC .2
#define TIMEOUT 120

using namespace std;

static void pin(int fd) {
  std::vector<char*> allocations;
  std::unordered_map<char*,int> allocSizes;
  unsigned long long memFootprint = 0;
  const int alloc_sizes[4] = {4096, 40960, 61440, 204800};

  // start the clock
  std::clock_t start;
  start = std::clock();

  // run for 60 seconds
  while ( (std::clock() - start) / (double) CLOCKS_PER_SEC < 120) {
    const int sz = rand() % 4;
    const int alignment = 4096;

    const int length = alloc_sizes[sz];
    char *buf = static_cast<char*>(memalign(alignment * 2, alloc_sizes[sz] + alignment));
    allocations.push_back(buf);
    allocSizes[buf] = length + alignment;
    memFootprint += length + alignment;

    int numRead = read(fd, buf, length);

    if (numRead < length)
      assert(!lseek(fd, 0, SEEK_SET));

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

    assert(allocations.size() == allocSizes.size());
  }

  while ( (std::clock() - start) / (double) CLOCKS_PER_SEC < TIMEOUT + 100)
    sleep(10000); 

  #if 0
  for (int i = 0; i < allocations.size(); i++) {
    char *victim = allocations[i];
    //delete [] victim;
    free(victim);
  }
  #endif
}

int main(int argc, char **argv) {
  int fd;

  assert(argc > 1);
  fd = open(argv[1], O_RDONLY | O_DIRECT);
  if (fd == -1) {
    cerr << "Error opening file!" << endl;
    exit(1);
  }

  pin(fd);

  close(fd);

  return 0;
}
