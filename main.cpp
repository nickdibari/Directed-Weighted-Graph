/* Nicholas DiBari                            */
/* Lab 5                                      */
/* 11/21/2015                                 */
/* lab5.cpp                                   */
/* Driver to test Implementation of GraphType */

#include "ItemType.h"
#include "VertexType.h"
#include "GraphType.h"
#include <queue>


int main(){
    //Initialize Graph
    GraphType graph;
    //Four vertices
    VertexType v1;
    VertexType v2;
    VertexType v3;
    VertexType v4;
    //Vertex value declaration
    v1.item.Initialize(10);
    v2.item.Initialize(20);
    v3.item.Initialize(30);
    v4.item.Initialize(40);
    //Adding vertices to Graph
    graph.AddVertex(v1);
    graph.AddVertex(v2);
    graph.AddVertex(v3);
    graph.AddVertex(v4);
    //Creates edges between 
    //1 -> 2
    //1 -> 3
    //2 -> 4
    graph.AddEdge(v1, v2, 1);
    graph.AddEdge(v1, v3, 2);
    graph.AddEdge(v2, v4, 4);
    //Prints Graph in Breadth First Traversal with v1 as the starting node
    //Should display 10 20 30 40
    graph.BreadthFirst(v1);
}