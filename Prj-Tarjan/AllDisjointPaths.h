#ifndef ALLDISJOINTPATHS_H
#define ALLDISJOINTPATHS_H
#include "Graph.h"
#include "Dijkstra.h"
class AllDisjointPaths
{
	public:
		AllDisjointPaths (std::string graphAddr);
		string * findPaths(int source, int destination);
	protected:
		Graph *G;
		Dijkstra *dik;
		string *paths;  
		
};


#endif

#ifndef ALLDISJOINTPATHS_H
#define ALLDISJOINTPATHS_H

class AllDisjointPaths
{
	public:
	protected:
};

#endif
