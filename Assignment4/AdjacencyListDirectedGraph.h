//
// AdjacencyListDirectedGraph.h  (Version 1.0)
// Kusdavletov Ernar, 20152008, kusdavletov1@unist.ac.kr
//

#ifndef ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
#define ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename V, typename E>
class AdjacencyListDirectedGraph {

  // ---------------------------------------------------------------------------------
  // You *cannot* add any additional public or private member functions in this class.
  // You *cannot* add any additional public or private member variables in this class.
  // ---------------------------------------------------------------------------------

public:

  // Define public data types of Vertex and Edge and the associated iterators.

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef typename VertexList::iterator VertexItor;
  typedef typename EdgeList::iterator EdgeItor;
  typedef typename VertexList::const_iterator VertexConstItor;
  typedef typename EdgeList::const_iterator EdgeConstItor;

private:

  // Define private data types of VertexObject and EdgeObject and the associated iterators.
  // The type of IncidenceEdgesList and its iterator are defined as well.

  struct VertexObject;
  struct EdgeObject;

  typedef list<VertexObject> VertexObjectList;
  typedef list<EdgeObject> EdgeObjectList;
  typedef list<EdgeList> IncidenceEdgesList;

  typedef typename VertexObjectList::iterator VertexObjectItor;
  typedef typename EdgeObjectList::iterator EdgeObjectItor;
  typedef typename IncidenceEdgesList::iterator IncidenceEdgesItor;

  /*
   * VertexObject stores data of a vertex.
   */
  struct VertexObject {
    V elt;                             // the element stored at this vertex
    VertexObjectItor pos;              // position in vertex_collection
    IncidenceEdgesItor inc_edges_pos;  // position in inc_edges_collection

    VertexObject(V _elt) : elt(_elt) {}  // pos and inc_edges_pos are initially "NULL".
  };

  /*
   * EdgeObject stores data of an edge.
   */
  struct EdgeObject {
    E elt;                          // the element stored at this edge
    Vertex origin_vertex;           // the vertex at the origin
    Vertex dest_vertex;             // the vertex at the destination
    EdgeObjectItor pos;             // position in edge_collection
    EdgeItor origin_inc_edges_pos;  // position in an edge list in inc_edges_collection
    EdgeItor dest_inc_edges_pos;    // position in an edge list in inc_edges_collection

    EdgeObject(const Vertex& v, const Vertex& w, E _elt) : origin_vertex(v), dest_vertex(w), elt(_elt) {} // pos origin_inc_edges_pos, and dest_inc_edges_pos are initially "NULL".
  };

  // ---------------------------------------------------------------------------------
  // This class should contain the following three member variables only:
  // vertex_collection, edge_collection, and inc_edges_collection
  // You are not allowed to define any other member variables (public or private).
  // ---------------------------------------------------------------------------------

  VertexObjectList vertex_collection;
  EdgeObjectList edge_collection;
  IncidenceEdgesList inc_edges_collection;
    public:
        class Vertex {

            VertexObject *v_obj;

            public:
                Vertex(VertexObject* v = NULL) : v_obj(v) {}

                V& operator*() const{
                    if (v_obj == NULL) throw runtime_error("NULL pointer.");
                    return v_obj->elt;
                }

                EdgeList incidentEdges() const{
                    if (v_obj == NULL) throw runtime_error("NULL pointer.");
                    return *(v_obj->inc_edges_pos);
                }

                bool isAdjacentTo(const Vertex& v) const{
                    if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL pointer.");
                    EdgeList temp = v.incidentEdges();
                    for (EdgeItor i = temp.begin(); i != temp.end(); i++){
                        if ((*i).origin() == *this && (*i).dest() == v)
                            return true;
                        if ((*i).origin() == v && (*i).dest() == *this)
                            return true;
                    }
                    return false;
                }

                bool isOutgoingTo(const Vertex& v) const{
                    if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL pointer.");
                    EdgeList temp = incidentEdges();
                    for (EdgeItor i = temp.begin(); i != temp.end(); i++){
                        if ((*i).dest() == v)
                            return true;
                    }
                    return false;
                }

                Edge outgoingEdge(const Vertex& v) const{
                    if (v_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL pointer.");
                    if (!isOutgoingTo(v)) throw runtime_error("Not outgoing edge");
                    EdgeList temp = incidentEdges();
                    for (EdgeItor i = temp.begin(); i != temp.end(); i++){
                        if ((*i).dest() == v)
                            return (*i);
                    }
                }

                EdgeList outgoingEdges() const{
                    EdgeList temp;
                    EdgeList temp_edges = incidentEdges();
                    for(EdgeItor i = temp_edges.begin(); i != temp_edges.end(); i++){
                        if((*i).origin() == *this)
                            temp.push_back(*i);
                    }
                    return temp;
                }

                bool operator==(const Vertex& v) const{
                    return (v_obj->elt == v.v_obj->elt && v_obj->inc_edges_pos == v.v_obj->inc_edges_pos && v_obj->pos == v.v_obj->pos) || (v_obj == v.v_obj);
                }

                friend class AdjacencyListDirectedGraph<V,E>;
        };

        class Edge {

            EdgeObject *e_obj;

            public:
                Edge(EdgeObject* e = NULL) : e_obj(e) {}

                E& operator*() const{
                    if (e_obj == NULL) throw runtime_error("NULL pointer.");
                    return e_obj->elt;
                }

                VertexList endVertices() const{
                    if (e_obj == NULL) throw runtime_error("NULL pointer.");
                    VertexList temp;
                    temp.push_back(e_obj->origin_vertex);
                    temp.push_back(e_obj->dest_vertex);
                    return temp;
                }

                Vertex opposite(const Vertex& v) const{
                    if (e_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL pointer.");
                    if (v == e_obj->origin_vertex)
                        return e_obj->dest_vertex;
                    else if (v == e_obj->dest_vertex)
                        return e_obj->origin_vertex;
                    else
                        throw runtime_error("No opposite vertex.");
                }

                bool isAdjacentTo(const Edge& edge) const{
                    if (e_obj == NULL || edge.e_obj == NULL) throw runtime_error("NULL pointer.");
                    if (e_obj->origin_vertex == edge.e_obj->origin_vertex || e_obj->origin_vertex == edge.e_obj->dest_vertex || e_obj->dest_vertex == edge.e_obj->origin_vertex || e_obj->dest_vertex == edge.e_obj->dest_vertex)
                        return true;
                    else
                        return false;
                }

                bool isIncidentOn(const Vertex& v) const{
                    if (e_obj == NULL || v.v_obj == NULL) throw runtime_error("NULL pointer.");
                    if (v == e_obj->origin_vertex || v == e_obj->dest_vertex)
                        return true;
                    else
                        return false;
                }

                Vertex origin() const{
                    if (e_obj == NULL) throw runtime_error("NULL pointer.");
                    return e_obj->origin_vertex;
                }

                Vertex dest() const{
                    if (e_obj == NULL) throw runtime_error("NULL pointer.");
                    return e_obj->dest_vertex;
                }

                bool isDirected() const{
                    if (e_obj == NULL) throw runtime_error("NULL pointer.");
                    if (e_obj->origin_vertex.v_obj == NULL || e_obj->dest_vertex.v_obj == NULL) throw runtime_error("Null can not be directed");
                    return true;
                }

                bool operator==(const Edge& edge) const{
                    return (e_obj->elt == edge.e_obj->elt && e_obj->origin_vertex == edge.e_obj->origin_vertex && e_obj->dest_vertex == edge.e_obj->dest_vertex) || (e_obj == edge.e_obj);
                }

                friend class AdjacencyListDirectedGraph<V,E>;
    };


    public:
        VertexList vertices(){
            VertexList temp;
            for (VertexObjectItor i = vertex_collection.begin(); i != vertex_collection.end(); i++){
                temp.push_back(Vertex(&(*i)));
            }
            return temp;
        }

        EdgeList edges(){
            EdgeList temp;
            for (EdgeObjectItor i = edge_collection.begin(); i != edge_collection.end(); i++){
                temp.push_back(Edge(&(*i)));
            }
            return temp;
        }

        Vertex insertVertex(const V& x){
            VertexObject *temp_vertex = new VertexObject(x);
            vertex_collection.push_back(*temp_vertex);
            temp_vertex->pos = --(vertex_collection.end());
            EdgeList temp_edges;
            inc_edges_collection.push_back(temp_edges);
            temp_vertex->inc_edges_pos = --(inc_edges_collection.end());
            Vertex vert(temp_vertex);
            return vert;
        }

        Edge insertDirectedEdge(const Vertex& v, const Vertex& w, E x){
            //if (v.isOutgoingTo(w)) throw runtime_error("Edge exists.");
            EdgeObject *temp_obj = new EdgeObject(v, w, x);
            edge_collection.push_back(*temp_obj);
            temp_obj->pos = --(edge_collection.end());
            Edge temp_edge(temp_obj);
            (*(v.v_obj->inc_edges_pos)).push_back(temp_edge);
            (*(w.v_obj->inc_edges_pos)).push_back(temp_edge);
            temp_edge.e_obj->origin_inc_edges_pos = --((*(v.v_obj->inc_edges_pos)).end());
            temp_edge.e_obj->dest_inc_edges_pos = --((*(w.v_obj->inc_edges_pos)).end());
            return temp_edge;
        }

        void eraseVertex(const Vertex& v){
            if (v.v_obj == NULL) throw runtime_error("NULL pointer.");
            for (VertexObjectItor i = vertex_collection.begin(); i != vertex_collection.end(); ++i){
                if (v.v_obj == &(*i))
                    vertex_collection.erase(i);
            }
            EdgeList temp = v.incidentEdges();
            for (EdgeItor i = temp.begin(); i != temp.end() ; ++i){
                eraseEdge(*i);
            }
            delete v.v_obj;
        }

        void eraseEdge(const Edge& e){
            if (e.e_obj == NULL) throw runtime_error("NULL pointer.");
            edge_collection.erase(e.e_obj->pos);
            (*(e.e_obj->origin_vertex.v_obj->inc_edges_pos)).erase(e.e_obj->origin_inc_edges_pos);
			(*(e.e_obj->dest_vertex.v_obj->inc_edges_pos)).erase(e.e_obj->dest_inc_edges_pos);
			delete e.e_obj;
        }
};

#endif //ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
