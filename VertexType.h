/* Nicholas DiBari                      */
/* Lab 5                                */
/* 11/21/2015                           */
/* VertexType.h                         */
/* Header file for VertexType structure */

#ifndef VERTEXTYPE_H
#define VERTEXTYPE_H
enum  MARK { DEFAULT, VISITED, QUEUED };


struct VertexType{
   
       ItemType item;
       MARK mark;        //default mark = DEFAULT; if visited, mark= VISITED; 
                        //if queued, mark = QUEUED;
     
};

#endif