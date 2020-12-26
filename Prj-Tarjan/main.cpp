/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include <iostream>
#include "Graph.h"
#include "Tarjan.h"
#include "SuurballeAlg.h"
#include "TarjanSRLG.h"
#include "AllDisjointPaths.h"
#include "BellmanFord.h"
using namespace std;


int main(int argc, char** argv) {
	Graph G;
	int source = 12 ;
	int destination =26;
	
	
	cout << "map of our network:" << endl;
	G.loadMap("Network.txt");
	//G.showMap();
	
	//........................................................................................
	//Suurballe-Tarjan Algorithm. calculates for all destinationes.
	cout << "finding paths using Suurballe-Tarjan algorithm:" << endl;
	Tarjan trj(G,source);
	trj.calculate();

	Path * x = trj.findPaths(destination);
	cout << x[0].getPath() << endl;
	cout << x[1].getPath() << endl;
	
	cout<< endl;cout<< endl;cout<< endl;
	
	//you use this to get the path in format of an integer array.
	//int *a = p[0].getAsArray();
	
	//...........................................................................................
	//Suurballe Algorithm. each time calculates for one destination.
	cout << "finding paths using Suurballe algorithm"<<endl;
	
	Graph map;
	map.loadMap("Network.txt");
	cout << "map of our network:" << endl;
	//map.showMap();
	SuurballeAlg s(map, source, destination);
	
	Path *p = s.calculateAlg();
	
	cout << p[0].getPath()<<endl;
	cout << p[1].getPath()<<endl;
	
	//............................................................................................
	//SRLG
	//
	cout << "................................................................"<<endl;
	TarjanSRLG t("network.txt", "SRLGEdges.data",0);         //by calling the costructor, we calculate tarjan once for this given source
	
	//change the below code in order to set affected SRLGs
	int SRLGs[] = {0,2};
	unsigned int  arrSize = sizeof(SRLGs)/sizeof(SRLGs[0]);  
	
	Path pSRLG = t.calculate(SRLGs,arrSize,20);    //SRLGNum is the number of SRLG that turns out to be deficient because of disaster
	cout << "The path that does not contain SRLG edges: " << pSRLG.getPath()<<endl;
//	G.loadSRLG("SRLGedges.data");
//	cout << G.ifSRGLContains("1-4",1)<<endl;
	
	//................................................................................................
	//finding all of the paths of a given source and destination:
	cout <<".................................................................."<<endl;
	AllDisjointPaths a("network.txt");
	string *paths = a.findPaths(20,10);
	for (int i=0;i<20;i++){
		cout <<"path No." <<i<<" is: "<<paths[i]<<endl;
	}
	//............................................................................................
	//Bhandari alg.
	cout << "..................................................................."<<endl;
	BellmanFord bl(0,"map.data");
	if(bl.calculate())
		cout << "found shortest paths!"<<endl;
	else
		cout << "there is one negative cycle, so unfortunately bellmanFord can not solve shortest paths!"<<endl;
	Path p10 = bl.getPath(6);
	cout << p10.getPath()<<endl;
	
	
}

