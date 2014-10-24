all:
	g++ fragment.cc -std=c++0x -o fragment
	g++ testalloc.cc -std=c++0x -o testalloc

testalloc: testalloc.cc
	g++ testalloc.cc -std=c++0x -o testalloc

fragment: fragment.cc
	g++ fragment.cc -std=c++0x -o fragment

clean:
	rm -rf testalloc
	rm -rf fragment
