#ifndef TARJANSRLG_H
#define TARJANSRLG_H
#include "Tarjan.h"
#include "Graph.h"
#include "Path.h"


class TarjanSRLG
{
	public:
		TarjanSRLG(string graphAddr, string SRLGAddr, int source);
		Path calculate(int *SRLGNum,int arrSize , int destination);
		
	protected:
		string prePath1;
		string prePath2;
		Tarjan *trj;
		Graph *G;
		int source;
		string *SRLG; //do we need it?
};

#endif
