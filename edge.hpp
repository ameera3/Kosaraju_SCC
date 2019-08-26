/*
 * Filename: edge.hpp
 * Description: Implements an edge class for a directed graph on
 *              which we will apply Kosaraju's SCC algorithm.
 */

#ifndef EDGE_HPP
#define EDGE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Forward declaration of vertex class
 */
class Vertex;

/* 
 * Class name: Edge
 * Instance Variables: source (vertex pointer to source)
 *                     dest (vertex pointer to dest)
 * Description: Implements an edge class for a directed graph 
 *              on which we will apply Kosaraju's SCC algorithm.                  
 * Public Methods: constructor
 * Private Methods: None                    
*/

class Edge {

    public:

        // Source
        Vertex* source;

        // Destination
        Vertex* dest;

        // Constructor 
        Edge(Vertex* tail, Vertex* head) :
            source(tail), dest(head) {} 

};

#endif // EDGE_HPP
