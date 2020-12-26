#include "TarjanSRLG.h"
#include <string>
#include <bits/stdc++.h> 

TarjanSRLG::TarjanSRLG(string graphAddr, string SRLGAddr, int source){
	this -> source = source;
	G = new Graph();
	G->loadMap(graphAddr);
	G->loadSRLG(SRLGAddr);
	trj = new Tarjan(*G,source);
	trj->calculate();
	prePath1 = "";
	prePath2 = "";
}

Path TarjanSRLG::calculate(int *SRLGNumbers,int arrSize ,int destination){
	
	

	Path * x = trj->findPaths(destination);
	
	
	//debug:
//	cout << "prePath1: " << prePath1 <<" length: " <<prePath1.length()<<  endl;
//	cout << "prePath2: " << prePath2 <<" length: " <<prePath2.length()<< endl;
	cout << "path1: " << x[0].getPath() <<endl;
	cout << "path2: " << x[1].getPath() <<endl;
	
	if ((x[0].getPath()==prePath1 && x[1].getPath()==prePath2) || (x[0].getPath()=="" && x[1].getPath()=="")){
		x[0].setPath("");
		return x[0];
	}

	string SRLGEdges;
	SRLGEdges = G->getSRLG(SRLGNumbers[0]);
	
	
	
	for (int i=1;i<arrSize;i++){
		SRLGEdges = SRLGEdges + "-"+G->getSRLG(SRLGNumbers[i]);
	}
	
	cout << "SRLG edges are: " << SRLGEdges << endl;

	
	//what if x[0] and x[1] do not contain any path, cousing after several iterations .....................?????
	
	
	
//	Path SRLG1;
//	Path SRLG2;
//	SRLG1.addToBegin(str);
//	cout <<str<<endl;
//    reverse(str.begin(), str.end()); 
//    cout << str<<endl; 
//	SRLG2.addToBegin(str);

	//checking whether we have one path that does not have a deficient edge based on the given SRLG
	
	bool flag = false;
	for (int i=0 ; i<x[0].getPathLength()-1;i++){
		string first = x[0].getSubPath(i,i+1);
		string second = x[0].getSubPath(i+1,i+2);
		string p1 = first + "-" + second;
		string p2 = second+"-"+first;
		//debug
		//cout << p1 << "   " << p2 << endl;
		if (SRLGEdges.find(p1) != std::string::npos) {
    		flag = true;
    		break;
		}
		if (SRLGEdges.find(p2) != std::string::npos) {
    		flag = true;
    		break;
		}
	}
	
	//cout << "flag is: "<<flag << endl;
	if (flag == false)
		return x[0];
		
		
	bool flag2 = false;
	// checking for the second path:
	for (int i=0 ; i<x[1].getPathLength()-1;i++){
		string first = x[1].getSubPath(i,i+1);
		string second = x[1].getSubPath(i+1,i+2);
		string p1 = first + "-" + second;
		string p2 = second+"-"+first;
		//debug
		//cout << p1 << "   " << p2 << endl;
		if (SRLGEdges.find(p1) != std::string::npos) {
    		flag2 = true;
    		break;
		}
		if (SRLGEdges.find(p2) != std::string::npos) {
    		flag2 = true;
    		break;
		}
	}
	//cout << "flag is: "<<flag2 << endl;
	if (flag2 == false)
		return x[1];
	//cout << "could not find any path so far" << endl;
	//if we can not find any path without having a SRLG edge, then we need to change the graph and recalculate tarjan Algorithm.
	
	Path SRLGpath;
	SRLGpath.addToBegin(SRLGEdges);
	//cout << SRLGpath.getPath()<<endl;
	//G -> showMap();
	//cout << endl<<endl;
	//removing SRLG edges from the graph:
	prePath1 = x[0].getPath();
	prePath2 = x[1].getPath();
	for (int i = 0 ; i<SRLGpath.getPathLength()-1;i=i+2 ){
		int  first = stoi(SRLGpath.getSubPath(i,i+1));
		int  second = stoi(SRLGpath.getSubPath(i+1,i+2));
		//only eliminating this given edge inside SRLG file, and not its reverse
		G->setEdge(first,second,-1);
		
		//debug:
		//cout << "first is: " << first << "  second is: " << second << ", operation is done." <<endl;
	}
	
	//G -> showMap();
	trj = new Tarjan(*G,source);
	trj->calculate();
	return calculate(SRLGNumbers,arrSize, destination);
		
	
}
