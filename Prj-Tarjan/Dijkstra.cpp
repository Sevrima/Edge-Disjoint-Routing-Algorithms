/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include <vector>
#include "Dijkstra.h"
#include "Graph.h"
#include <map>


Dijkstra::Dijkstra(int source, Graph map ){
	this -> source=source;
	this -> map=map;
	dist = new int[map.getvNum()];
	g = new vector<pair<int,int>>[map.getvNum()];
}

void Dijkstra::calculate(){
	int n = map.getvNum();
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int x=map.getEdge(i,j);
			if(x != -1) {
				g[i].push_back({j,x});
			}
		}
	}
	
	for(int i=0; i<n; i++) 
		dist[i] = 1e8;
	
	//it is a max priority_queue, we enter minus of numbers to have a min priority_queue
	//in priority queue: first is the label of node and second one is number of node
	pq.push({0, source});
	dist[source] = 0;
	while(pq.size()) {
		auto e = pq.top(); pq.pop();
		int u = e.second;
		int d = -e.first;
		if(dist[u] < d) continue;
		for(auto v : g[u]) {
			if(dist[v.first] > d + v.second) {
				dict[v.first]=e.second;
				dist[v.first] = d + v.second;
				pq.push({-dist[v.first], v.first});
			}
		}
	}
	
	//distances and dictionary are now ready.
	//for(int i=0; i<n; i++) cout << i << " " << dist[i] << endl;
	//for(int i=0;i<n;i++)
	//	cout <<i << "   "<<dict[i]<<endl;
}

string Dijkstra::getPath(int source, int destination){
	int pre = this ->getPredecessor(destination);
	if (pre==-1)
		return "";
		
	string p = "";
	
	p = to_string(destination);
	
	while(pre != -1){
		p = to_string(pre)+"-"+p;
		pre = this -> getPredecessor(pre);
	}
	return p;
}

int Dijkstra::getPredecessor(int node){
	if (dict.count(node))
		return dict[node];
	else
		return -1;
}

float Dijkstra::getDist(int node){
	return dist[node];
}

void Dijkstra::setDict(int node, int value){
	dict[node] = value;
}

