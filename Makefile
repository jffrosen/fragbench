all:
	g++ fragment.cc -std=c++0x -o fragment
	g++ testalloc.cc -std=c++0x -o testalloc

testalloc: testalloc.cc
	g++ testalloc.cc -std=c++0x -o testalloc

fragment: fragment.cc
	g++ fragment.cc -std=c++0x -o fragment

pin: fragment_pin.cc
	g++ -std=c++0x fragment_pin.cc -o fragment_pin

clean:
	rm -rf testalloc
	rm -rf fragment
	rm -rf fragment_pin
