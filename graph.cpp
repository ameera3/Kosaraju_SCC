/*
 * Filename: graph.cpp
 * Description: Implements a directed graph class for 
 *              Kosaraju's SCC algorithm.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h> 
#include "graph.hpp"
#include <limits>

// number of SCCs to report
#define NUM_SCC 5

using namespace std;

/*
 * Constructor of the graph
 */ 
Graph::Graph(void) : time(0) {}

/*
 * Load the digraph from a list of its edges.
 * Every row indicates an edge, the vertex label in first 
 * column is the tail and the vertex label in second column 
 * is the head (recall the graph is directed, and the edges 
 * are directed from the first column vertex to the second 
 * column vertex).
 *
 * in_filename - input filename
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool Graph::loadFromFile(const char* filename) {

	// used to get each line from input file
	string line;

	// input file stream
	ifstream * in = new ifstream(filename);

	// Raise an error if file can't be read and return false
	if (in->eof()) {
		cerr << "Failed to read " << filename << "!\n";
		return false;
	}

	while (getline(*in, line)) {
		stringstream ss;
		// Storing the line into stringstream
		ss << line;

		// used for parsing the line
		string temp;

		// current tail vertex
		unsigned int currentTail;

		// current head vertex
		unsigned int currentHead;

		// extracting current tail;
		ss >> temp;

		// check current tail is unsigned int
		if( stringstream(temp) >> currentTail ){

			/*  search for vertex in current list of
			 *  vertices. If it's not there, create
			 *  a new vertex and add it to the current
			 *  list of vertices
			 */  
			Vertex* currTail = vertex_map[currentTail];
			if(currTail == nullptr){
				currTail = new Vertex(currentTail);
				vertex_map[currentTail] = currTail;
			}

			// extracting current head
			ss >> temp;

			// check current head is unsigned int
			if ( stringstream(temp) >> currentHead ){

				/* search for vertex in current list
				 * of vertices. If it's not there, 
				 * create a new vertex and add it to
				 * the current list of vertices.
				 */
				Vertex* currHead = vertex_map[currentHead];
				if(currHead == nullptr){
					currHead = new Vertex(currentHead);
					vertex_map[currentHead] = currHead;
				}

				/* add edge to currTail's outEdges and
				 * to currHead's inEdges
				 */
				(currTail->outEdges).push_back(currHead);
				(currHead->inEdges).push_back(currTail);
			}

			/* To save from space at the end of string */
			temp = ""; 
		}
		ss.str("");
	}

	delete in;
	return true;

}

/*
 * Depth First Search -- initiates depth first search from node n
 *
 * n - Vertex* pointer representing vertex
 * s - Vertex* pointer to leader
 * edgesRev - boolean indicating if we are running DFS 
 *            with edges reversed
 *                                     
 */

unsigned int Graph::DFS(Vertex* n, Vertex* s, bool edgesRev) { 

	// used to iterate over n's out edges or in edges
	vector<Vertex*>::iterator it;

	// iterator pointing to end of n's out edges or in edges
	vector<Vertex*>::iterator end;

	/* used to count how many times DFS with a given leader
	 * is called
	 */
	unsigned int count = 1;

	/* set explored parameter of n to true and
	 * set leader of n to be s
	 */
	n->explored = true;
	n->leader = s;

	/* if edges reversed, iterate over all incoming edges
	 * of n. Otherwise, iterate over all outgoing edges.
	 */
	if( edgesRev ){
		it = (n->inEdges).begin();
		end = (n->inEdges).end();
	}
	else{
		it = (n->outEdges).begin();
		end = (n->outEdges).end();
	}

	/* if an in/out neighbor of n is not yet explored
	 * call DFS from it and add its count to the running
	 * total.
	 */
	for ( ; it != end; ++it ) {
		if( !((*it)->explored) ) {
			count += DFS(*it, s, edgesRev);
		}
	}

	/* Increment time, set the finishing time of n
	 * and update the fTime map if this is the first pass
	 */
	++time;
	if( edgesRev ) {
		n->fTime = time;
		fTime_map[time] = n;
	}

	// return total number of times DFS with leader s is called
	return count;
} 

/* 
 * Resets the explored parameter of all the vertices
 * as we need to run DFS twice.
 */
void Graph::reset() {

	for( auto it = vertex_map.begin(); it != vertex_map.end(); ++it ){
		(it->second)->explored = false;
	}
}

/*
 * Kosaraju's SCC Algorithm
 *            
 */

vector<pair<unsigned int, Vertex*>> Graph::Kosaraju() {

	// used to keep track of current leader vertex
	Vertex* currentLeader;

	// used to iterate through vertices
	Vertex* currentVertex;

	// vector of sizes returned
	vector<pair<unsigned int, Vertex*>> sizes;

	// used to switch between vertex_map and fTime_map
	unordered_map<unsigned int, Vertex*> mapping = vertex_map;

	/* used to keep track of how many times
	 * DFS is called with a current leader vertex
	 */
	unsigned int count;

	/* used to keep track if we are running DFS
	 * with edges reversed or not.
	 */
	bool edgesRev = true;

	// number of vertices
	unsigned int n = vertex_map.size();

	// used for iterating
	unsigned int i;

	// used for iterating
	unsigned int j;

	// Run DFS twice
	for(j = 0; j < 2; ++j){

		/* On the second pass, reset the time, the 
		 * explored parameter of all vertices, process
		 * the edges with their original direction,
		 * and use finishing time to order the vertices
		 */
		if( j % 2 ){
			time = 0;
			edgesRev = false;
			reset();
			mapping = fTime_map;
		}

		/* Always start with the largest label (name or finishing
		 * time) and process down to the smallest. If the current
		 * vertex is not explored, set the current leader to be the
		 * current vertex and run DFS. On the second pass store, 
		 * the count and the current leader in a priority queue
		 * so that we can find the five largest components
		 */
		for( i = n; i > 0; --i) {
			currentVertex = mapping[i];
			if ( !(currentVertex->explored) ){
				currentLeader = currentVertex;
				count = DFS(currentVertex, currentLeader, edgesRev);
				if( j % 2 ){
					leaders.push(make_pair(count, currentLeader));
				}	
			}	
		}
	}

	// save the current size of the priority queue leaders. Otherwise, 
	// every time you pop this will decrease the size.
	unsigned int qSize = leaders.size();

	/* Fill the vector to return */
	for(j = 0; j < qSize && j < NUM_SCC; j++) {
		pair<unsigned int, Vertex*> temp = leaders.top();
		sizes.push_back(temp);
		leaders.pop();
	}

	return sizes;

}    


/*
 * Destructor: Iterate through the vertex map and delete all vertices
 */

Graph::~Graph() {

	for ( auto it = vertex_map.begin(); it != vertex_map.end(); ++it ){
		delete it->second;
	}

}
