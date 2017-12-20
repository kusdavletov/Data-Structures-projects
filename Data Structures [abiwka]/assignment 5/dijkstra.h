#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "minheap.h"
#include <iostream>

/**
 * Assignment 5 for CSE221 Data Structures
 *
 * 2015. 11. 2
 *
 */


class graphNode {
public:
	unsigned int idx;  // vertex index
	double weight;     // edge weight
	graphNode* link;   // link to next node
	graphNode () {
	    idx = 0;
	    weight = 0;
	    link = NULL;
	};
	graphNode (unsigned int i, double w, graphNode *l = NULL) {
	    idx = i;
	    weight = w;
	    link = l;
	};
};

// Dijkstra class
class Dijkstra {
public:
	Dijkstra() {
	    N = M = 0;
	    d = NULL;
	    p = NULL;
	    mheap = NULL;
	    adjList = NULL;
    };
	~Dijkstra();

	void ReadGraph(const char* file);

	double FindPath(const unsigned int v0, const unsigned int v1);

private:
    bool *u;
    double *d;
    unsigned int N, M, *p;
	MinHeap* mheap;
	graphNode* adjList;
};

#endif
