#include <iostream>
#include "AdjacencyListDirectedGraph.h"

using namespace std;


int main()
{
	AdjacencyListDirectedGraph<string,double> graph;
	AdjacencyListDirectedGraph<string,double>::Vertex FIR = graph.insertVertex("FIR");
	AdjacencyListDirectedGraph<string,double>::Vertex SEC = graph.insertVertex("SEC");
	AdjacencyListDirectedGraph<string,double>::Vertex THR = graph.insertVertex("THR");
	AdjacencyListDirectedGraph<string,double>::Vertex FOU = graph.insertVertex("FOU");
	AdjacencyListDirectedGraph<string,double>::Vertex FIV = graph.insertVertex("FIV");
	AdjacencyListDirectedGraph<string,double>::VertexList vertexlist = graph.vertices();
	for (list<AdjacencyListDirectedGraph<string,double>::Vertex>::iterator it=vertexlist.begin(); it!=vertexlist.end() ; ++it)
    {
    	cout << " " << *it.operator*();
	}
	cout << "19" << endl;
	AdjacencyListDirectedGraph<string,double>::EdgeList adj = FIR.incidentEdges();
	cout << "21" << endl;
	AdjacencyListDirectedGraph<string,double>::Edge FIRtoSEC = graph.insertDirectedEdge(FIR, SEC, 2);
	cout << "23" << endl;
	AdjacencyListDirectedGraph<string,double>::Edge FIRtoTHR = graph.insertDirectedEdge(FIR, THR, 3);
	cout << "25" << endl;
	AdjacencyListDirectedGraph<string,double>::Edge FIRtoFOU = graph.insertDirectedEdge(FIR, FOU, 4);
	cout << "27" << endl;
	AdjacencyListDirectedGraph<string,double>::Edge FIRtoFIV = graph.insertDirectedEdge(FIR, FIV, 5);
	cout << "29" << endl;
	AdjacencyListDirectedGraph<string,double>::EdgeList adj2 = graph.edges();
	cout << "31" << endl;
	cout << "FIR" << " isAdjacentTo " << FIR.isAdjacentTo(SEC) << " SEC" << endl; //1
	cout << "FIR" << " isAdjacentTo " << FIR.isAdjacentTo(THR) << " THR" << endl; //1
	cout << "FIR" << " isAdjacentTo " << FIR.isAdjacentTo(FOU) << " FOU" << endl; //1
	cout << "FIR" << " isAdjacentTo " << FIR.isAdjacentTo(FIV) << " FIV" << endl; //1

	cout << "SEC" << " isAdjacentTo " << SEC.isAdjacentTo(THR) << " THR" << endl; //1
	cout << "SEC" << " isAdjacentTo " << SEC.isAdjacentTo(FIV) << " FIV" << endl; //1
	cout << "FIV" << " isAdjacentTo " << FIV.isAdjacentTo(FOU) << " FOU" << endl; //1
	cout << "FIV" << " isAdjacentTo " << FIV.isAdjacentTo(THR) << " THR" << endl; //1

	cout << "FIR" << " isOutgoingTo " << FIR.isOutgoingTo(SEC) << " SEC" << endl; //1
	cout << "FIR" << " isOutgoingTo " << FIR.isOutgoingTo(THR) << " THR" << endl; //1
	cout << "FIR" << " isOutgoingTo " << FIR.isOutgoingTo(FOU) << " FOU" << endl; //1
	cout << "FIR" << " isOutgoingTo " << FIR.isOutgoingTo(FIV) << " FIV" << endl; //1

	cout << "SEC" << " isOutgoingTo " << SEC.isOutgoingTo(SEC) << " SEC" << endl; //1
	cout << "SEC" << " isOutgoingTo " << SEC.isOutgoingTo(THR) << " THR" << endl; //1
	cout << "THR" << " isOutgoingTo " << THR.isOutgoingTo(FOU) << " FOU" << endl; //1
	cout << "THR" << " isOutgoingTo " << THR.isOutgoingTo(FIV) << " FIV" << endl; //1

	AdjacencyListDirectedGraph<string,double>::EdgeList outgoingFIR = FIR.outgoingEdges();
	AdjacencyListDirectedGraph<string,double>::Edge outgoingFIRtoSEC = FIR.outgoingEdge(SEC);
	cout << "Check if outgoing From FIR to SEC " << (outgoingFIRtoSEC == FIRtoSEC) << endl;
	cout << "Check if edges are equal " << (outgoingFIRtoSEC == FIRtoFIV) << endl;
	AdjacencyListDirectedGraph<string,double>::Edge outgoingFIRtoTHR = FIR.outgoingEdge(THR);
	cout << "Check if outgoing From FIR to THR " << (outgoingFIRtoTHR == FIRtoTHR) << endl;
	cout << "Check if edges are equal " << (outgoingFIRtoTHR == FIRtoFIV) << endl;

	cout << "Check if opposite THR to FIR " << (FIRtoTHR.opposite(THR) == FIR) << endl;
    cout << "Check if opposite FIR to THR " << (FIRtoTHR.opposite(FIR) == THR) << endl;
	cout << "Check if opposite THR to FIV " << (FIRtoTHR.opposite(THR) == FIV) << endl;

    AdjacencyListDirectedGraph<string,double>::EdgeList edgelist = graph.edges();
	for (list<AdjacencyListDirectedGraph<string,double>::Edge>::iterator it = edgelist.begin(); it!=edgelist.end() ; ++it)
    {
    	cout << " " << *it.operator*();
	}
	cout << endl;
    graph.eraseEdge(FIRtoTHR);
    graph.eraseEdge(FIRtoFIV);
	AdjacencyListDirectedGraph<string,double>::EdgeList a = FIR.outgoingEdges();
    //graph.eraseVertex(FIR);
   	//AdjacencyListDirectedGraph<string,double>::EdgeList vertexlist2 = FIR.outgoingEdges();

	AdjacencyListDirectedGraph<string,double>::VertexList vertexlist2 = graph.vertices();
	AdjacencyListDirectedGraph<string,double>::EdgeList edgelist2 = graph.edges();

	for (list<AdjacencyListDirectedGraph<string,double>::Edge>::iterator it=edgelist2.begin(); it!=edgelist2.end() ; ++it)
    {
    	//cout << edgelist2.size();
    	cout << " " << *it.operator*();
	}
	cout << endl;
    for (list<AdjacencyListDirectedGraph<string,double>::Vertex>::iterator it=vertexlist2.begin(); it!=vertexlist2.end() ; ++it)
    {
    	cout << " " << *it.operator*();
	}

	return 0;
}
