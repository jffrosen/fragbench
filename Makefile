TARGETS = testalloc fragment
OBJS = testalloc.o fragment.o
CXX := g++
LD := g++
CFLAGS = 
LDFLAGS = 

TIMER_DIR = ./rdtscp_timer

all: timer fragment testalloc

timer:
	cd $(TIMER_DIR); $(MAKE)

testalloc: testalloc.cc timer
	g++ $(TIMER_DIR)/timing.o testalloc.cc -std=c++0x -lrt -o testalloc

fragment: fragment.cc
	g++ fragment.cc -std=c++0x -o fragment

clean:
	rm -rf testalloc
	rm -rf fragment
	rm -rf *.txt *.csv
