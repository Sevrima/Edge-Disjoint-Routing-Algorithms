/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/

#ifndef PATH_H
#define PATH_H

#include <string>
using namespace std;
class Path
{
	public:
		void addToBegin(string p);
		void addToEnd(string p);
		string getPath();
		int* getAsArray();
		int getPathLength();
		void setPath(string str);
		string getSubPath(int n, int m);     //n to m-1
		
	private:
		string path;
		
		
};

#endif


