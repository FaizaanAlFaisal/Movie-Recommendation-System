#ifndef MYGRAPHS_CPP
#define MYGRAPHS_CPP

#include <iostream> 
#include "VectorImplementation.cpp" //my vectors implementation
//#include "MergeSort.cpp" //sorting 

using namespace std;

template <class T> class GraphList;
template <class T> class GraphVertex; //forward declarations

template <class T> class GraphEdge
{
public:
    GraphVertex<T>* destination; //source not needed, as it will exist within the adjacency vector for source
    double weight; //weight associated with this edge. positive for cost, negative for reward

    GraphEdge(GraphVertex<T>* d = NULL, const double& w = 1) : destination(d), weight(w) {}
    //constructor for edges
  
    //no additional functions needed for edges, as they are managed by vertices and graphlists
    //sort edges based on their weight alone, overload operators to account for this
    friend bool operator<(const GraphEdge<T>& e1, const GraphEdge<T>& e2)
    {
        return e1.weight < e2.weight;
    }
    friend bool operator>(const GraphEdge<T>& e1, const GraphEdge<T>& e2)
    {
        return e1.weight > e2.weight;
    }
    friend bool operator==(const GraphEdge<T>& e1, const GraphEdge<T>& e2)
    {
        return e1.weight == e2.weight;
    }
    friend bool operator!=(const GraphEdge<T>& e1, const GraphEdge<T>& e2)
    {
        return e1.weight != e2.weight;
    }
};


template <class T> class GraphVertex
{
public:
    T data; //whatever information the node contains
    Vector<GraphEdge<T>> adjacentTo; //a list of nodes this node can access

    GraphVertex(const T& value) : data(value) {} //list remains uninitialized until edges are manually inserted

    void addEdge(GraphVertex<T>* destination, double weight) //add an edge to a certainn node
    {
        adjacentTo.push_back(GraphEdge<T>(destination, weight)); //simply create a new edge and push back
    }

    void removeEdge(GraphVertex<T>* dest) //remove an edge to a certain node
    {
        for (int i = 0; i < adjacentTo.size(); i++)
        {
            if (adjacentTo.arr[i].destination == dest) //if array index matches destination node
            {
                //adjacentTo.arr[0].destination;
                adjacentTo.erase(i); 
                return;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const GraphVertex<T>& v) //overloading operator for printing
    {
        os << "\033[0;36m Vertex Information: " << v.data << "\033[0m \n";
        os << " List of all nodes adjacent: \n";
        for (int i = 0; i < v.adjacentTo.size(); i++) //print info of all destination nodes and weights between them:
        {
            //adjacentTo contains edges, which contain destination nodes, and weights
            GraphEdge<T>* tempEdge = v.adjacentTo.arr[i]; //temporarily store the edge
            GraphVertex<T>* destVert = tempEdge->destination;
            cout << " Weight of Connection: " << tempEdge->weight;
            cout << destVert->data; 
        }
        return os;
    }
};



template <class T> class GraphList
{
public:
    bool isDirected; //false if undirected, true if directed graph
    // unsigned int numNodes = 0; //initialize at 0
    Vector<GraphVertex<T>* > vertices; //list of nodes this graph contains

    GraphList(bool isDirGraph = false) : isDirected(isDirGraph) {}
    //undirected graph by default, but can decide at time of construction

    //commented out portion checks for duplicates and prevents them, unnecessary check for our proj, so it is excluded
    void addVertex(const T& value) 
    {
        //GraphVertex<T>* temp;
        //for (int i = 0; i < vertices.size(); i++)
        //{
        //    temp = vertices.arr[i];
        //    if (temp->data == value) //not allowing duplicate entries
        //        return;
        //}
        //vertices.push_back(GraphVertex<T>(value)); //create a new vertex and push into list
        GraphVertex<T>* newVertex = new GraphVertex<T>(value); 
        vertices.push_back(newVertex); //create a new vertex and push into list
    }

    void removeVertex(const T& value) //unnecessary for project, but implemented anyway
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.arr[i]->data == value) //if data found
            {
                GraphVertex<T>* toRemove = vertices.arr[i]; //remove this vertex from all other edges
                vertices.erase(i); //delete the element at i

                GraphVertex<T>* temp;
                for (int i = 0; i < vertices.size(); i++)
                {
                    temp = vertices.arr[i];
                    temp->removeEdge(toRemove); //remove edges adjacent to node that was removed
                }
                delete temp;
                return;
            }
        }
    }

    //helpful for alternative logic to our current program. implemented for generic use in future
    /*void addEdge(const T& source, const T& dest, double weight)
    {
        GraphVertex<T>* s = NULL, *d = NULL; 
        GraphVertex<T>* temp;
        for (int i = 0; (i < vertices.size() && (s == NULL || d == NULL)); i++)
        {
            temp = vertices.arr[i]; //store temp
            if (temp->data == source)
                s = temp; 
            if (temp->data == dest)
                d = temp;
            
        }
        if (s == NULL || d == NULL) return; //if either source or destination was not determined, insert no edges
        else
        {
            s->addEdge(d, weight); //add edge from s to d with weight
            if (!isDirected) d->addEdge(s, weight); //if undirected graph, add complementary edge too
        }
    }

    void removeEdge(const T& source, const T& dest) //similar logic to above
    {
        GraphVertex<T>* s, *d; //source and destination vertex ptrs
        GraphVertex<T>* temp; //temp ptr to store each vertex of graph
        for (int i = 0; (i < vertices.size() && (s == NULL || d == NULL)); i++)
        {
            temp = vertices.arr[i];
            if (temp->data == source) 
                s = temp;
            if (temp->data == dest)
                d = temp;
        }
        if (s == NULL || d == NULL) return; //if either source or destination is undetermined, remove no edge
        else
        {
            s->removeEdge(d);
            if (!isDirected) //if graph is undirected, remove complementary edge as well
                d->removeEdge(s);
        }
    }*/
};

#endif