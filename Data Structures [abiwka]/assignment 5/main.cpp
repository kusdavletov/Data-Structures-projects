#include "dijkstra.h"
#include <iostream>

/**
 * Assignment 5 for CSE221 Data Structures
 *
 * 2015. 11. 2
 *
 */


int main()
{
	Dijkstra ds;

	ds.ReadGraph("input.txt");

	std::cout << "Shortest path between 0 and 36422 : ";

	double res = ds.FindPath(0,6);

	std::cout << "Distance : " << res << "\n";

	return 0;
}
