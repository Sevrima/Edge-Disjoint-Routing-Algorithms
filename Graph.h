/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#ifndef GRAPH_H
#define GRAPH_H


#include <string>
#include <iostream> 
#include <queue> 



class Graph {
public:
    Graph();
    virtual ~Graph();
    void loadMap(std::string adr);
    void loadSRLG(std::string adr);
    int getvNum();
    void showMap();
    void setEdge(int i, int j,float val);
    float getEdge(int i, int j);
    std::string getSRLG(int number);
    bool ifSRGLContains(std::string edge, int SRLGNumber);
    
    
private:
    int vNum;       //number of nodes
    int numOfSRLGs;
    int **matrixMap;    // the matrix containing -1, +1, and 0 for each edge
    std::string *SRLG;
    
    
    

};


#endif

