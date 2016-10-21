/* Nicholas DiBari              */
/* Lab 5                        */
/* 11/21/2015                   */
/* GraphType.h                  */
/* Header File for GraphType    */


#ifndef GRAPHTYPE_H
#define GRAPHTYPE_H

#include <iostream>
#include <queue>
#include "ItemType.h"
#include "VertexType.h"
using namespace std;

class GraphType{

   public:

        GraphType();
        GraphType(int max);

        ~GraphType();

        bool IsEmpty() const;
        bool IsFull() const;

        void AddVertex(VertexType v);
        void AddEdge(VertexType v1, VertexType v2, int w);
  
        void DeleteVertex(VertexType v);
        void DeleteEdge(VertexType v1, VertexType v2);

        int GetWeight(VertexType v1, VertexType v2);

        bool EdgeExists(VertexType v1, VertexType v2);
        bool VertexExists(VertexType v);

        void Print(VertexType v);

        void MarkVertex(VertexType v, MARK m);//mark whether the vertex has been visited or queued

        void GetNeighbors(VertexType v);

        //Function to Print Graph in Breadth-First Traversal
        void BreadthFirst(VertexType start);

    private:

        int numberOfVertices;
        int maxVertices;
        
        VertexType * vertices; //save all the vertices

        int edges[50][50];   //save all the edges

        queue<VertexType> nq; //queue to hold vertices for Breadth First Traversal

        
        int IndexIs(VertexType v);

};

#endif