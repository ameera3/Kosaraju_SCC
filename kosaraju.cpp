/*
 * Filename: kosaraju.cpp
 * Usage: ./kosaraju File
 * Description: The command line program kosaraju.cpp
 *	        takes in one parameter, an input file
 *		name. The input file specified by the
 *		input file name should contain a list 
 *		of its edges. Every row indicates an 
 *		edge, the vertex label in first column 
 *		is the tail and the vertex label in 
 *		second column is the head. The program 
 *		will output the size of the five largest
 *		strongly connected components.
 */

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
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

	// vector returned by Kosaraju
	vector<pair<unsigned int, Vertex*>> results;

	// create a new instance of graph
	Graph* G = new Graph();

	// load graph from text file
	G->loadFromFile(argv[IN_IDX]);
		
	// run Kosaraju and print the sizes and leaders of the 
	// top five components.
	results = G->Kosaraju();
	for(unsigned int i = 0; i < results.size(); ++i) {
		cout << results[i].first << *results[i].second << endl;
	}		

	// no memory leaks here
	delete G;
}
	

