#ifndef TOURISM_H
#define TOURISM_H

#include "Graph.h"

class CTourism {
public:
	void CreateGraph();
	void GetSpotInfo();
	void TravelPath();
	void FindShortPath();
	void DesignPath();
	
private:
	CGraph graph;
};

void menu();

#endif
