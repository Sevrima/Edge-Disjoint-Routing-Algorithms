/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#ifndef SUURBALLEALG_H
#define SUURBALLEALG_H

#include "Graph.h"
#include "Dijkstra.h"
#include "Path.h"

class SuurballeAlg
{
	public:
		SuurballeAlg(Graph map, int source, int destination);
		Path* calculateAlg();
		
	private:
		void transform();
		void makeGv();
		Graph G;
		//Graph Gv;  -> no need for it, we can only have G 
		int source;
		int destination;
		Dijkstra *dic1;
		Dijkstra *dic2;
		
	
};

#endif

