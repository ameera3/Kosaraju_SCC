/*
 * Filename: karger.cpp
 * Usage: ./karger File
 * Description: The command line program karger.cpp
	        takes in one parameter, an input file
		name. The input file specified by the
		input file name should contain the
		adjacency list representation of a 
		simple undirected graph. The program
		will output the minimum cut in the graph.
 */

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include <math.h> 
#include <limits>
#include "graph.hpp"

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

using namespace std;

// Main Driver
int main(int argc, char** argv) 
{

	//Check for Arguments
	if (argc != EXPECTED_ARGS){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	// create a new instance of graph
	Graph* G = new Graph();

	// load graph from text file
	G->loadFromFile(argv[IN_IDX]);
	unsigned int V = (G->vertex_map).size();
	unsigned int minCut = std::numeric_limits<unsigned int>::max();
	unsigned int repeat = (unsigned int) ceil(pow(V,2)*log(V));	

	for(unsigned int i = 0; i < repeat; ++i) { 
	  unsigned int thisCut = G->Karger();
		if( thisCut < minCut ){
			minCut = thisCut;
		}	
		G->reset();
	}
	cout << "Min Cut: " << minCut << endl;
	delete G;
}
	

