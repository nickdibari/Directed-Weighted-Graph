/* Nicholas DiBari              */
/* Lab 5                        */
/* 11/21/2015                   */
/* GraphType.cpp                */
/* Implementation for GraphType */

#include "GraphType.h"

//Default Constructor
GraphType::GraphType(){
    numberOfVertices=0;
    maxVertices=50;
    vertices = new VertexType [maxVertices];
}

//Initialization Constructor
//Set max number of vertices equal to parameter value
GraphType::GraphType(int max){
    numberOfVertices=0;
    maxVertices=max;
    vertices = new VertexType [maxVertices];
}

//Destructor
//Delete dynamically allocated array of vertices
GraphType::~GraphType(){
    delete[] vertices;
    numberOfVertices=0;
}

//Checks if Graph is Empty
bool GraphType::IsEmpty() const{
    return numberOfVertices == 0;
}

//Checks if Graph is Full
bool GraphType::IsFull() const{
    return numberOfVertices == maxVertices;
}

//Add Vertex to Graph
//Pre: Graph is not Full
void GraphType::AddVertex(VertexType v){
    //Check to ensure that Graph is not full
    if (!IsFull()){
        //Add vertex to Graph
        int pos_to_store=numberOfVertices;
        vertices[pos_to_store]=v;
        v.mark=DEFAULT; 
        numberOfVertices++;
    }
}

//Delete Vertex from Graph
//Pre: Graph is not Empty, Vertex must exist in Graph
void GraphType::DeleteVertex(VertexType v){
    //Vertex must exist in Graph
    if (VertexExists(v)){
        //Delete all edges connected to vertex
        for (int i=0; i<numberOfVertices; i++){
            if (EdgeExists(v, vertices[i])){
                DeleteEdge(v, vertices[i]);
            }
        }    
        //Get index of vertex to be deleted
        int pos_to_delete= IndexIs(v);
        //Get index of last vertex in vertices[]
        int replacement = numberOfVertices-1; //number of vertices=n; 
        //position of last vertex in vertices[] is n-1
        
        //Replace the vertex to be deleted with the vertex last in vertices[]
        vertices[pos_to_delete]=vertices[replacement];
    
        //Decrement number of Vertices in Graph
        numberOfVertices--;
    }

}

//Add Edge to Graph
//Pre: The two vertices must exist in the Graph
void GraphType::AddEdge(VertexType v1, VertexType v2, int w){
    //Check to make sure v1 and v2 are in Graph
    if (VertexExists(v1) && VertexExists(v2)){
        int v1_pos = IndexIs(v1); //v1_pos = v1 position in vertices[]
        int v2_pos = IndexIs(v2); //v2_pos = v2 position in vertices[]
        //Store weight in edges[][] corresponding to the the two positions
        //of v1 and v2
        edges[v1_pos][v2_pos]=w;
    }  
}

//Delete Edge from Graph
//Pre: Edge must already exist between two vertices
void GraphType::DeleteEdge(VertexType v1, VertexType v2){
    //Check to make sure Edge exists between v1 and v2
    if (EdgeExists(v1,v2)){
        int v1_pos = IndexIs(v1); //v1_pos = v1 position in vertices[]
        int v2_pos = IndexIs(v2); //v2_pos = v2 position in vertices[]
    
        //Set edges[v1_pos][v2_pos] equal to 0 in order to delete the edge 
        //between v1 and v2
        edges[v1_pos][v2_pos]=0;
    }
}

//Returns weight stored in edge
//Pre: Edge must exist between two vertices
//If no edge exists, function returns -1
int GraphType::GetWeight(VertexType v1, VertexType v2){
    //Check that edge exists between v1 and v2
    if (EdgeExists(v1, v2)){
        int v1_pos = IndexIs(v1); //v1_pos = v1 position in vertices[]
        int v2_pos = IndexIs(v2); //v2_pos = v2 position in vertices[]
        //Return value of edges[v1_pos][v2_pos]
        return edges[v1_pos][v2_pos];
    }
    //If edge does not exist, function should return -1 to indicate error
    return -1;
}

//Edge Exists
//Return whether of not edge exists between two vertices
bool GraphType::EdgeExists(VertexType v1, VertexType v2){
    //Check that v1 and v2 are in Graph
    if (VertexExists(v1) && VertexExists(v2)){
        int v1_pos = IndexIs(v1); //v1_pos = v1 position in vertices[]
        int v2_pos = IndexIs(v2); //v2_pos = v2 position in vertices[]
        //If value at edges[v1_pos][v2_pos] is greater than 0, there must be an 
        //edge between v1 and v2
        if (edges[v1_pos][v2_pos]>0){
            return 1;
        }
        //Else no edge exists, return false
        return 0;
    }
}

//Vertex Exists
//Returns whether or not vertex exists in graph
bool GraphType::VertexExists(VertexType v){
    //Check to make sure Graph is not Empty
    if (!IsEmpty()){
        //Go through array of vertices
        for (int i=0; i<numberOfVertices; i++){
            //If vertex at i equals to vertex v, return True
            if (vertices[i].item.ComparedTo(v.item) == EQUAL){
                return 1;
            }
        }
        //Else vertex is not in Graph, return False
        return 0;
    }
}

//Mark Vertex 
//Marks whether vertex has been visited or added to the queue
//Pre: Vertex is in Graph
void GraphType::MarkVertex(VertexType v, MARK m){
    //Check to make sure Vertex is in Graph
    if (VertexExists(v)){
        //Set the mark of vertex equal to the mark passed as the parameter
        v.mark=m;
    }
}

//Get Neighbors
//Retrieves neighbors of a vertex in the graph
//Pre: Vertex Exists in Graph
void GraphType::GetNeighbors(VertexType v){
    //Check to ensure Vertex is in Graph
    if(VertexExists(v)){
        //Go through vertices[] to find a vertex that has an edge with v
        for (int i=0; i<numberOfVertices; i++){
            //If edge exists between the vertices AND the vertex is not marked
            //as queued or visited
            if(EdgeExists(v, vertices[i]) && (vertices[i].mark==DEFAULT)){
                   //Mark neighbor as queued, add neighbor to queue
                   nq.push(vertices[i]); //add vertices[i] to queue
                   MarkVertex(vertices[i], QUEUED); //mark vertices[i] as queued

            } 
        }
    }
}

//Print
//Print Vertex
//Pre: Vertex is in Graph
void GraphType::Print(VertexType v){
    //Check to make sure Vertex exists
    if (VertexExists(v)){
        //Print information held by ItemType stored in VertexType
        v.item.Print();
    }
}

//BreadthFirst
//Print Graph in Breadth First Traversal
//VertexType passed as a parameter is the starting vertex
//Pre: Vertex is in Graph
void GraphType::BreadthFirst(VertexType start){
    //Make sure that Vertex Exists in Graph
    if(VertexExists(start)){
        //Print start
        Print(start);
        //Set start to VISITED
        MarkVertex(start, VISITED);
        //Add start neighbors to queue
        GetNeighbors(start);
        //Main Loop for Traversal
        while(!nq.empty()){
            //Get next vertex to perform traversal on
            VertexType next_vertex;
            next_vertex = nq.front();
            //Print Vertex
            Print(next_vertex);
            //Mark vertex as visited
            MarkVertex(next_vertex, VISITED);
            //Get Neighbors of vertex
            GetNeighbors(next_vertex);
            //Dequeue 
            nq.pop();
        }
    }
}

//Index Is
//Private member function that returns index of vertex in the array
//Pre: Vertex is in Graph
//Post: Returns position of vertex in vertices[]
//If vertex is not in graph, returns -1
int GraphType::IndexIs(VertexType v){
    //Check to make sure Graph is not empty
    if (!IsEmpty()){
        //Go through array of vertices
        for (int i=0; i<numberOfVertices; i++){
            //If item in vertices[i] is equal to item in v, return i (pos of v 
            //in vertices[])
            if (vertices[i].item.ComparedTo(v.item) == EQUAL){
                return i; //Position of v in vertices[]
          }
        }
        //If no value returned at this point, vertex does not exist. Function
        //should return -1 to indicate vertex does not exist in the graph
        return -1;
    
    }
}