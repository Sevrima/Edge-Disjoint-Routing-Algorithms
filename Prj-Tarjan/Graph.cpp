/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::loadMap(string adr){
    fstream inFile;
    
    inFile.open(adr);
    if (!inFile){
        cout << "Unable to open the file containing graph!";
        return;
    }
    inFile >> vNum;
    matrixMap = new int*[vNum];
    for (int i=0;i<vNum;i++){
        matrixMap[i]=new int[vNum];
    }  
    
    for (int i=0;i<vNum;i++){
        for (int j=0;j<vNum;j++){
            matrixMap[i][j]=-1;
        }
    }
    
    int v1,v2;
    float edge;
    while (inFile >>v1 ){
    	inFile >> v2;
    	inFile >> edge;
    	matrixMap[v1][v2] = edge;
	}
    
}
string Graph::getSRLG(int number){
	return SRLG[number];
}
void Graph::loadSRLG(string adr){
    fstream inFile;
    
    inFile.open(adr);
    if (!inFile){
        cout << "Unable to open the file containing SRLG edges!";
        return;
    }

    inFile >> numOfSRLGs;
    SRLG = new string[numOfSRLGs];
    for (int i=0;i<numOfSRLGs;i++){
    	int numOfEdges;
    	inFile >> numOfEdges;
		SRLG[i] = "";
		string first = "";
		string second = "";
        for (int j=0;j<numOfEdges;j++){
            inFile >> first;
            inFile >> second;
            //saving both edges and its reverse
            if (SRLG[i] == ""){
				SRLG[i] = first+"-"+second;
			}   
			else{
				SRLG[i] = SRLG[i] +"-"+ first+"-"+second;
			}
        }
        //debug:
        //cout << SRLG[i]<<endl;
    	}
    
    
}  
    
bool Graph::ifSRGLContains(std::string edge, int SRLGNumber){
	if (SRLG[SRLGNumber].find(edge) != std::string::npos) {
    	return true;
	}
	return false;
}

void Graph::showMap(){
    for (int i=0;i<vNum;i++){
        for (int j=0;j<vNum;j++){
            //cout << matrixMap[i][j]<<" "; 
            printf("%3d ",matrixMap[i][j]);
        }
        cout << endl;
    }
}
int Graph::getvNum(){
    return vNum;
}

void Graph::setEdge(int i, int j, float val){
	matrixMap[i][j]=val;
	
}

float Graph::getEdge(int i , int j){
	return matrixMap[i][j];
}

