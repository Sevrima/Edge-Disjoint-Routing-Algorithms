/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Path.h"
#include <Map>
#include <vector>
#include <queue>
using namespace std;

class Dijkstra
{
	public:
		
		Dijkstra(int source ,Graph x);
		void calculate();
		int getPredecessor(int node);	//returns the predecessur of each given node
		float getDist(int node);
		void setDict(int node , int value);
		string getPath(int source, int destination);
	private:
		map <int,int> dict;
		vector < pair <int, int> > *g;   //****
		int *dist;						//*****
		int source;
		Graph map;
		priority_queue < pair <int, int> > pq;
		
};

#endif

