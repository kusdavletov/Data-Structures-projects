//
// assignment4.h  (Version 1.0)
// Kusdavletov Ernar, 20152008, kusdavletov@unist.ac.kr
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <limits>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"

double FlightMap::calcRouteDistance(const list<string> route){
    double distance = 0;
    string prev;
    for (list<string>::iterator i = route.begin(); i != route.end(); i++){
        if (!isAirportExist(*i)) throw runtime_error("Such airport does not exist.");
        if (i == route.begin()){
            prev = *i;
        }
        else{
            if (!isConnectionExist(prev, *i)) throw runtime_error("No such connection");
            FlightGraph::Vertex origin, dest;
            findAirport(origin, prev);
            findAirport(dest, *i);
            FlightGraph::Edge dis = origin.outgoingEdge(dest);
            distance = distance + *dis;
            prev = *i;
        }
    }
    return distance;
}

list<string> FlightMap::findRoute(const string &airport1, const string &airport2) {
    if (!isAirportExist(airport1) || !isAirportExist(airport2)) throw runtime_error("Such airport does not exist.");
    list<string> temp = findReachableAirports(airport1);
    list<string> temp_routes;
    FlightGraph::Vertex air1, air2;
    findAirport(air1, airport1);
    findAirport(air2, airport2);
    for (list<string>::iterator i = temp.begin(); i != temp.end(); i++){
        if (*i == airport2){
            temp_routes.push_back(*(air1.outgoingEdge(air2)));
        }
    }
    return temp_routes;
}


list<string> FlightMap::findReachableAirports(const string &airport) {
    if (!isAirportExist(airport)) throw runtime_error("Such airport does not exist.");
    list<string> airportsCollection;
    FlightGraph::Vertex airport_vertex;
    findAirport(airport_vertex, airport);
    FlightGraph::EdgeList temp = airport_vertex.incidentEdges();
    for (FlightGraph::EdgeItor i = temp.begin(); i != temp.end(); i++){
        airportsCollection.push_back(*(i->opposite(airport_vertex)));
    }
    return airportsCollection;
}

list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
    if (!isAirportExist(airport1) || !isAirportExist(airport2)) throw runtime_error("Such airport does not exist.");
}

void FlightMap::printAllShortestRoutes(const string &airport) {
    if (!isAirportExist(airport)) throw runtime_error("Such airport does not exist.");
}
