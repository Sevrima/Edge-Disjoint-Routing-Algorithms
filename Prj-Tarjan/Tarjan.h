/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#ifndef TARJAN_H
#define TARJAN_H

#include "Graph.h"
#include "Dijkstra.h"
#include "Path.h"
#include <queue>


class Tarjan{
	public:
		Tarjan(Graph G, int source);
		void calculate();
		Path* findPaths(int destination);
		int getpFor(int node);
		int getqFor(int node);
	private:
		void transform();
		bool areInSameTree(int node1, int node2);
		void showLables();
		int source;
		map <int,int> pdict;
		map <int,int> qdict;
		priority_queue < pair <int, int> > pq;
		int *dist;
		bool *lableFlag;  //to separate trees from their nodes
		Graph G;
		Dijkstra * dij1;
		
};

#endif
