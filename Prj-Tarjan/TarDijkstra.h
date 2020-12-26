/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#ifndef TarDIJKSTRA_H
#define TarDIJKSTRA_H

#include "Graph.h"
#include <Map>
#include <vector>
#include <queue>
using namespace std;

class TarDijkstra
{
	public:
		public:
		TarDijkstra(int source ,Graph x);
		void calculate();
		int getPredecessor(int node);	//returns the predecessur of each given node
		float getDist(int node);
	private:
		map <int,int>pdict;
		map <int,int>qdict;
		vector < pair <int, int> > *g;   //****
		int *dist;						//*****
		int source;
		Graph map;
		priority_queue < pair <int, int> > pq;
		
};

#endif

