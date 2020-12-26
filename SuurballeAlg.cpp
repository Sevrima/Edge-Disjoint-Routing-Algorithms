/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include "SuurballeAlg.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "Path.h"


 SuurballeAlg::SuurballeAlg(Graph G , int source , int destination){
 	this -> source = source;
 	this -> destination = destination;
 	this -> G = G;
 	
 }
 
 Path* SuurballeAlg::calculateAlg(){
 	
 	//step 0: running dijkstra alg. over the graph
 	dic1 = new Dijkstra(source , G);
 	dic1->calculate();
 	
 	
 	//step 1: conducting the transformation over the graph
 	this->transform();
 	
	//debug: transformed graph 
	//G.showMap();
	
	//step 2: creating the Gv graph and running dijkstra on it 
 	this->makeGv();   //not G is turned to be Gv
 
 	//Debug: Gv
 	//G.showMap();
 	dic2 = new Dijkstra(source , G);
	dic2->calculate();

	
	//step3 and step4:
	//removing the reversed edges and grouping the remaining paths together, so that we can make 
	//two edge-disjoint path from source to destination

	//finding first path from G:
	Path path1;
	int v1,v2;
	v2 = destination;
	v1;
	//path1 = to_string(v2);
	path1.addToBegin(to_string(v2));
	while( v2 != source ){
		v1=dic1->getPredecessor(v2);
		//path1=path1+" "+to_string(v1);
		path1.addToEnd(to_string(v1));
		v2=v1;
	}
	
	
	//finding second path from Gv:
	Path path2;
	v2 = destination;
	//path2 = to_string(v2);
	path2.addToBegin(to_string(v2));
	while( v2 != source ){
		v1=dic2->getPredecessor(v2);
		//path2 = path2 +" "+ to_string(v1);
		path2.addToEnd(to_string(v1));
		v2=v1;
	}
	
	string edgeDisjointPath1 = "";
	string edgeDisjointPath2 = "";

	//DEBUG
	//ex: 1
//	path1.setPath("0-2-3-1-5");
//	path2.setPath("0-6-7-8-5-7-3-2");
	
	//ex: 2
//	path1.setPath("0-1-2-3-4-5-9");    
//	path2.setPath("0-0-0-0-5-4-3-2-1-6-7-8-9") ;
	//cout << path1.getPath()<<endl;
	//cout << path2.getPath()<<endl;
	
//	path1.setPath("211-12-14-1-7");
	
	
	bool flag1 = 0;
	for (int i=0 ; i< path1.getPathLength()-1;i++){
		for (int j=0 ; j< path2.getPathLength()-1;j++){
			
			if (path1.getSubPath(i,i+1) != path2.getSubPath(j+1,j+2)){
				continue;
			}
			if (path1.getSubPath(i+1,i+2) != path2.getSubPath(j,j+1)){
				continue;
			}
			
			if (i<=j){
				edgeDisjointPath1 = path1.getSubPath(0,i+1) +"-"+ path2.getSubPath(j+2,path2.getPathLength());	
			}
			
			if (i>j){
				edgeDisjointPath1 = path2.getSubPath(0,j+1) +"-"+ path1.getSubPath(i+2,path1.getPathLength());
			}
			
			flag1 = 1;
			break;
		}
		if (flag1 == 1 )
			break;
	}
	
	
	int flag2 = 0;
	for (int i=path1.getPathLength()-1 ; i>=0 ;i--){
		
		for (int j=0 ; j< path2.getPathLength()-1;j++){
			
			if (path1.getSubPath(i,i+1) != path2.getSubPath(j,j+1))
				continue;
				
			if (path1.getSubPath(i-1,i) != path2.getSubPath(j+1,j+2))
				continue;
			
			
			if (i<=j){
				
				edgeDisjointPath2 = path2.getSubPath(0,j) +"-"+ path1.getSubPath(i,path1.getPathLength());
			}
			
			if (i>j){	
				edgeDisjointPath2 = path2.getSubPath(0,j+1) +"-"+ path1.getSubPath(i+1,path1.getPathLength());
			}
			
			flag2 = 1;
			break;
		}
		if (flag2 == 1 )
			break;
	}
	
	if (flag1 == 0 && flag2 == 0){
		edgeDisjointPath1 = path1.getPath();
		edgeDisjointPath2 = path2.getPath();
	}
	
	//eliminating the extra "-"
	if(edgeDisjointPath1.at(edgeDisjointPath1.length()-1)=='-')
		edgeDisjointPath1 = edgeDisjointPath1.substr(0,edgeDisjointPath1.length()-1);
	if(edgeDisjointPath2.at(edgeDisjointPath2.length()-1)=='-')
		edgeDisjointPath2 = edgeDisjointPath2.substr(0,edgeDisjointPath2.length()-1);
		
	//saving the path into path1 and path2:
	
	path1.setPath(edgeDisjointPath1);
	path2.setPath(edgeDisjointPath2);
	//cout << "edge disjoint path one is: " << path1.getPath() << endl;
	//cout << "edge disjoint path two is: " << path2.getPath() << endl;
	//reversing the paths:   -->in some cases it is being reversed ...

	if (path1.getSubPath(0,1)!=to_string(source)){
		int p1Size = path1.getPathLength();
		string str = "";
		for (int i=0 ; i<p1Size;i++){
			if (str=="")
				str = path1.getSubPath(p1Size-1-i,p1Size-i);
			else
				str = str +"-"+ path1.getSubPath(p1Size-1-i,p1Size-i);
		}	
		
		path1.setPath(str);
	}
	

	if (path2.getSubPath(0,1)!=to_string(source)){
		int p2Size = path2.getPathLength();
		string str = "";
		for (int i=0 ; i<p2Size;i++){
			if (str=="")
				str = path2.getSubPath(p2Size-1-i,p2Size-i);
			else
				str = str +"-"+ path2.getSubPath(p2Size-1-i,p2Size-i);
		}	
		
		path2.setPath(str);
	}	
	
	Path * p = new Path[2];
	p[0] = path1;
	p[1] = path2;
	return p;

 }
 
 void SuurballeAlg::transform(){
 	
	for (int i=0;i<G.getvNum();i++){
		for (int j=0;j<G.getvNum();j++){
			if (G.getEdge(i,j)!=-1){
				float d = G.getEdge(i,j)+dic1->getDist(i)-dic1->getDist(j);
				//saving the transformed graph instead of the previous graph 
				G.setEdge(i,j,d);
			}
		}
	}
	
 }
 
 void SuurballeAlg::makeGv(){
 	int w = destination;
 	
	while (true){
		//w and v are two endes of last edge 
		if (w==source)
			break;

		int v = dic1->getPredecessor(w);
		G.setEdge(w,v,G.getEdge(v,w));
		G.setEdge(v,w,-1);
		w=v;	
	}
 }
 
 

