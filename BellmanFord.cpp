#include "BellmanFord.h"

BellmanFord::BellmanFord(int source, std::string graphAddr){
	this -> source = source;
	G = new Graph();
	G -> loadMap(graphAddr);
	G -> showMap();
	dist = new int[G->getvNum()];
	
}

int BellmanFord::calculate(){
	int vNum = G->getvNum();
	
	for (int i=0 ; i<vNum;i++){
		dist[i] = 1e8;
	}
	
	dist[source] = 0;
	
	for (int k=0 ; k<vNum-1;k++){
		for (int i=0;i<vNum;i++){
			for (int j=0;j<vNum;j++){
				if (G->getEdge(i,j) == -1)
					continue;
				if (dist[j]>dist[i]+G->getEdge(i,j)){
					dict[j] = i;
					dist[j] = dist[i]+G->getEdge(i,j);
				}
			}
		}	
	}
	
	for (int i=0;i<vNum;i++){
		for (int j=0;j<vNum;j++){
			if (G->getEdge(i,j) == -1)
				continue;
			if (dist[j]>dist[i]+G->getEdge(i,j)){
				return 0;
			}
		}
	}	
	return 1;
	
}
int BellmanFord::getPredecessor(int node){
	if (dict.count(node))
		return dict[node];
	else
		return -1;	
}

Path BellmanFord::getPath(int destination){
	Path p;
	int pre = destination;
	
	//debug:
//	cout <<"dict valudes:"<<endl;
//	for (int i=0 ; i<G->getvNum();i++)
//		cout << "i: " << i<< "dict value: " << getPredecessor(i)<<endl;

	do{
		p.addToBegin(to_string(pre));
		pre = getPredecessor(pre);
	}while(pre != -1);
	
	return p;
}




