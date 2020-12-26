#ifndef BELLMANFORD_H
#define BELLMANFORD_H
#include "Graph.h"
#include <Map>
#include "Path.h"
class BellmanFord
{
	public:
		BellmanFord(int source, std::string graphAddr);
		int calculate();
		Path getPath(int destination);
		int getPredecessor(int node);
	protected:
		int *dist;
		std::map <int,int> dict;
		Graph *G;
		int source;
};

#endif
