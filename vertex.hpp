/*
 * Filename: vertex.hpp
 * Description: Implements a vertex class for a directed graph 
 *              on which we will apply Kosaraju's SCC algorithm. 
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

/* 
 * Class name: Vertex
 * Instance Variables: name (unsigned int containing vertex's label)
 *                     leader (keeps track of which vertex the DFS
 *                             originated from)
 *                     fTime (finishing time)
 *		       explored (marks whether the vertex has been
 *                               explored by DFS or not)
 * Description: Implements a vertex class for a directed graph on
 *              which we will apply Kosaraju's SCC algorithm.
 * Public Methods: constructor
 * Private Methods: None                    
*/

class Vertex {

    public:

        // vertex label
        unsigned int name;

        // vertex leader -- DFS originated from here
        Vertex* leader;

        // finishing time
        unsigned int fTime;

	// explored
	bool explored;

	// outgoing edges
	vector<Vertex*> outEdges;

	// incoming edges
	vector<Vertex*> inEdges;

        // Constructor that constructs a node with the given label.
        Vertex(unsigned int& label) :
            name(label), leader(nullptr), fTime(label), explored(false) {} 

};

/* Overload operator<< to print a Vertex's fields to an ostream. */
inline ostream & operator <<(ostream& stm, const Vertex& v) {
    stm << '[';
    stm << setw(10) << &v;                   // Vertex address
    stm << "; n:" << v.name;                 // Vertex name
    stm << "; l:" << setw(10) << v.leader;   // Vertex leader
    stm << "; t:" << v.fTime;                // Vertex finishing time
    stm << "; o:" << (v.outEdges).size();    // Number of outgoing arcs
    stm << ']';
    return stm;
}

#endif // VERTEX_HPP
