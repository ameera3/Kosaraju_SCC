# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: kosaraju   

kosaraju: graph.o

graph.o: graph.hpp vertex.hpp  

clean:
	rm -f kosaraju *.o core* *~

