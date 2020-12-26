/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include "Tarjan.h"
#include "Graph.h"
#include <vector>
#include "Dijkstra.h"


Tarjan::Tarjan(Graph G, int source){
	this -> G = G;
	this -> source = source;
	dist = new int[G.getvNum()];
	lableFlag = new bool[G.getvNum()];
}

void Tarjan::calculate() {
	
	//running dijkstra once:
	dij1 = new Dijkstra(source , G);
	dij1 -> calculate();
	
	//implementing the transformation:
	this -> transform();
	
	
	for(int i=0; i<G.getvNum(); i++) {
		lableFlag[i] = false;
		dist[i] = 1e8;
	}
	//we save the (labeles, nodes) inside of the priority queue
	pq.push({0,source});
	dist[source]=0;
	while(pq.size()){
		auto min = pq.top(); 
		pq.pop();
		int minNode = min.second;
		int minLable = -min.first;
		//Debug
		//cout << "**********************************************************************" <<endl;
		//cout << "min selected is: (lable, node) -> " << minNode << " " << minLable <<endl;
		//first for loop ........................................................................................................
		for (int i=0 ; i<G.getvNum();i++){
			
			int edge = G.getEdge(minNode,i);
			
			if (edge ==-1)
				continue;
			
			if (dij1->getPredecessor(i) == minNode  ){
				//deleting the edges exiting the minNode from the tree (dij1)
				//dij1 -> setDict(i,-1);
				continue;
			}
			
			if (minLable + edge < dist[i]){
				dist[i] = minLable + edge;
				pdict[i] = minNode;
				qdict[i] = minNode; 
				pq.push({-dist[i],i});
			}
		}
		
		lableFlag[minNode] = true;
		//Debug:
		//lableFlag[6] = true;
		//cout << "new AreIn... : " << areInSameTree(4,6)<<endl;
		//showLables();
		
		
		//second for loop ....................................................................................................
		//Debug: printing pdictionary
		//for (int i=0 ; i<G.getvNum();i++)
		//	cout <<i<<" "<<dij1 -> getPredecessor(i)<<endl;
		
		
		//looping through non-tree edges:
		for (int i = 0 ; i < G.getvNum(); i++){
			for (int j = 0 ; j < G.getvNum();j++){
				int edge = G.getEdge(i,j);
				if (edge == -1)
					continue;
				
				
				if (dij1->getPredecessor(j) == i ||  (dij1->getPredecessor(j) == -1 )){
					continue;
				}
				if (areInSameTree(i,j))
					continue;
				//Debug:
				//cout << "i and j being processed in the second loop: " << i << " " << j << endl;
				//ok
				if (minLable + edge < dist[j]){
					//cout << "2nd second loop: " << i << " " << j <<endl;
					//ok
					dist[j] = minLable + edge;
					pdict[j] = i;
					qdict[j] = minNode; 
					pq.push({-dist[j],j});
				}
				
			}
		}
	
	
	
	
	//Debug:
	//showLables();
	
	
	}

	//debug:
	//showLables();
//Debug:
//	int size = pq.size();
//	
//	for (int i = 0 ; i < size ; i++){
//		cout << " pq : " << pq.top().first << " " << pq.top().second<<endl;
//		pq.pop();
//		
//	}
	
}

void Tarjan::transform(){
 	
	for (int i=0;i<G.getvNum();i++){
		for (int j=0;j<G.getvNum();j++){
			if (G.getEdge(i,j)!=-1){
				float d = G.getEdge(i,j)+dij1->getDist(i)-dij1->getDist(j);
				//saving the transformed graph instead of the previous graph 
				G.setEdge(i,j,d);
			}
		}
	}
	
 }
 
 bool Tarjan::areInSameTree(int node1, int node2){
 	int cpNode1 = node1;
 	int cpNode2 = node2;
 	
 	if (node1 == node2 || (dij1 -> getPredecessor(node1)==node2) || (dij1->getPredecessor(node2)==node1))
 		return true;
 		
 		
 	//case 1: backtracking node 1
 	while (dij1 ->getPredecessor(node1)!=-1 && lableFlag[dij1 -> getPredecessor(node1)]==false ){
		node1 = dij1 ->getPredecessor(node1);
	}
	if (node1 == node2 || (dij1 -> getPredecessor(node1)==node2) || (dij1->getPredecessor(node2)==node1))
 		return true;
 	
 	//case2: backtracking node 2	
 	node1 = cpNode1;
 	node2 = cpNode2;
	while (dij1 ->getPredecessor(node2)!=-1 && lableFlag[dij1 -> getPredecessor(node2)]==false ){
		node2 = dij1 ->getPredecessor(node2);
	}
	if (node1 == node2 || (dij1 -> getPredecessor(node1)==node2) || (dij1->getPredecessor(node2)==node1))
 		return true;
 		
 		
	//case 3: backtracking both nodes: 		
	node1 = cpNode1;
 	node2 = cpNode2;
	while (dij1 ->getPredecessor(node2)!=-1 && lableFlag[dij1 -> getPredecessor(node2)]==false ){
		node2 = dij1 ->getPredecessor(node2);
	}
	while (dij1 ->getPredecessor(node1)!=-1 && lableFlag[dij1 -> getPredecessor(node1)]==false ){
		node1 = dij1 ->getPredecessor(node1);
	}
	if (node1 == node2 || (dij1 -> getPredecessor(node1)==node2) || (dij1->getPredecessor(node2)==node1) )
		return true;
	else
		return false;
 }
 
 
 int Tarjan::getpFor(int node){
 	if (pdict.count(node))
		return pdict[node];
	else
		return -1;	
 }
 
 
 int Tarjan::getqFor(int node){
 	if (qdict.count(node))
		return qdict[node];
	else
		return -1;
 }
 
 
 void Tarjan::showLables(){
 	for (int i=0 ; i < G.getvNum() ; i++){
 		cout << "Node: "<<i<<"  p, and q are: " << dist[i] << " " << getpFor(i)<< " " << getqFor(i)<<endl;
	 }
 }
 
 
 
 Path* Tarjan::findPaths(int destination){
 	string * str = new string[2];
 	str[0] = "";
 	str[1] = "";
 	
 	// d(destination) is not finite, there is only one path available for this destination
 	
 	if (dist[destination] == 1e8){    //means infinite
 		//can not find 2 edge disjoint path. so we only return the path that was found in Dijkstra alhorithm.

 		Path *p = new Path[2];
		p[0].setPath("");
		p[1].setPath("");
		if ( dij1 -> getPredecessor(destination)==-1)
			return p;
		
		str[0] = to_string(destination);
 		while (destination != source){
 			destination = dij1 -> getPredecessor(destination);
			str[0] =  to_string(destination) + "-"+str[0];
			
		}
		
		p[0].setPath(str[0]);
		return p;
 	}
 	
 	 	
 	map <int,int> mark;
 	mark[destination]=1;

 	int n = destination;
 	//initialization:
 	while(getqFor(n) != -1){
		n = getqFor(n); 
 		mark[n]=1;
 	}
 	
 	//extracting the first edge-disjoint path:
 	n = destination;
 	str[0] = to_string(destination);
 	while(n !=source){
 		if (mark[n] == 1){
 			mark[n] = 0;
 			
 			n = getpFor(n);
 			str[0] = to_string(n)+"-"+str[0];
			continue;
		}	
		if (mark[n] == 0){
			
			n = dij1 -> getPredecessor(n);
			str[0] = to_string(n) + "-" +str[0];
		}
	}
	
	
	//extracting the second edge-disjoint path:
	n = destination;
	str[1] = to_string(destination);
	while(n !=source){
 		if (mark[n] == 1){
 			mark[n] = 0;
 			n = getpFor(n);
 			str[1] = to_string(n)+"-"+str[1];
			continue;
		}	
		if (mark[n] == 0){
			
			n = dij1 -> getPredecessor(n);
			str[1] = to_string(n) + "-" +str[1];
		}
	}
	Path* p = new Path[2];
	p[0].setPath(str[0]);
	p[1].setPath(str[1]);
 	return p;
 }
