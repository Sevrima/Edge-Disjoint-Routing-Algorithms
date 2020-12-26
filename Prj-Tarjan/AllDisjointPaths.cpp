#include "AllDisjointPaths.h"
#include "Graph.h"
#include "Dijkstra.h"

AllDisjointPaths::AllDisjointPaths(std::string graphAddr){
	G = new Graph();
	G->loadMap(graphAddr);
	paths = new string[20]; //for simplicity, at max it finds 100 edge-disjoint paths for a given srouce and destination!!
}

string * AllDisjointPaths::findPaths(int source, int destination){
	
	
	int c = 0;
	do{
		dik = new Dijkstra(source, *G);
		dik->calculate();
		paths[c] = dik ->getPath(source, destination);
		//cout << "----One found path is: " << paths[c]<<endl;
		Path p;
		p.setPath(paths[c]);
		for (int i = 0 ; i<p.getPathLength()-1;i++ ){
			int  first = stoi(p.getSubPath(i,i+1));
			int  second = stoi(p.getSubPath(i+1,i+2));
			//cout <<"first is: " << first << " second is: " << second<<endl;
			//only eliminating this given edge inside SRLG file, and not its reverse
			G->setEdge(first,second,-1);
			
			//debug:
			//cout << "first is: " << first << "  second is: " << second << ", operation is done." <<endl;
		}
		c++;
	}while(paths[c-1] != "");
	
	return paths;
}

#include "AllDisjointPaths.h"
