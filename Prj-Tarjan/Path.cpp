/*
	- by amir 
	- implementation of suurballe and suurballe-tarjan algorithms for finding two minimum-length edge-disjoint paths
	- may, 8, 2019
*/
#include "Path.h"
#include <string>

void Path::addToEnd(string p){
	if (path.length()==0)
		path = p;
	else{
		path = path +"-"+ p;
	}
}

void Path::addToBegin(string p){
	if (path.length()==0)
		path = p;
	else{
		path = p + "-" + path;
	}
}

string Path::getPath(){
	return path;
}

int Path::getPathLength(){
	int c=0;
	for (int i=0; i<path.length();i++){
		if (path.at(i)=='-')
			c++;
	}
	return c+1;
}
void Path::setPath(string str){
	path = str;
}
string Path::getSubPath(int n, int m){        //-> returns elements from n to m (m is not included)
	string p="";
	int c = 0;
	int pos1 = 0;
	int pos2 = 0;
	//n and m has to be an acceptable number:
	int elementsNum = this -> getPathLength();
	if (m>elementsNum || n<0||n>elementsNum-1||m<0)
		return "";
	while(true){
		
		if (n == 0){
			pos1 = 0;
			break;
		}
		
		pos1 = path.find("-",pos1)+1;
		c++;
		if (c<n)
			continue;
		break;
	}
	
	c=0;
	while(true){
		if (m == 0){
			pos2 = 0;
			break;
		}
		
		pos2 = path.find("-",pos2+1);
		c++;
		
		if (c<m)
			continue;
		break;	
	}
	
	p = path.substr(pos1,pos2-pos1);		
	return p;
}

int * Path::getAsArray(){
	int size = getPathLength();
	int * arr = new int[size];
	for (int i =0 ; i<size; i++){
		arr[i] = stoi(getSubPath(i,i+1));
	}	
	return arr;
}


