/*
 * Filename: graph.hpp
 * Description: Implements a directed graph class for 
 *              Kosaraju's SCC algorithm.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include "vertex.hpp"

using namespace std;

/* 
 * Class name: Graph
 * Instance Variables: vertex_map (unordered map of vertex labels 
 *				   and corresponding vertex pointers)
 *		       fTime_map (unordered map of vertex finishing times
 * 				  and corresponding vertex pointers)
 *		       leaders (priority queue of leaders along with the
 *                              size of the corresponding SCC)
 * Description: Implements a directed graph class for Kosaraju's
 *		SCC algorithm.
 * Public Methods: constructor, destructor, loadfromFile, Kosaraju, DFS
 * Private Methods: None                    
*/

class Graph {

public:

     unsigned int time;		

    /* Unordered map of vertex labels and 
     *	corresponding vertex pointers
     */
    unordered_map<unsigned int,Vertex*> vertex_map;

    /* Unordered map of vertex finishing times and
     * corresponding vertex pointers
     */
    unordered_map<unsigned int, Vertex*> fTime_map;

    // Priority Queue of Leaders
    priority_queue< pair<unsigned int, Vertex*> > leaders;

    /**
     * Constructor of the graph
     */
    Graph(void);

    /*
     * Load the graph from its adjacency list representation.
     *
     * in_filename - input filename
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* filename);

    /* Destructor */
    ~Graph();

    /*
     * Depth First Search -- initiates depth first search from
     *                       node n
     *
     * n - Vertex* pointer to node that we are starting DFS from
     * s - Vertex* pointer to leader of s
     *
     */

     /*
      * Resets the explored parameter of all the vertices
      */
    void reset();

    unsigned int DFS( Vertex* n, Vertex* s, bool edgesRev);

    /*
     * Kosaraju's Algorithm
     * 
     */ 
    vector<pair<unsigned int, Vertex*>> Kosaraju();
};


#endif // GRAPH_HPP
