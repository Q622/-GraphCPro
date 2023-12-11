#ifndef GRAPH_H
#define GRAPH_H

#define SIZE 20
#define INF 0x3f3f3f3f
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

struct Vex {
	int num;               //景点编号
	std::string name;      //景点名
	std::string info;      //其他信息
};

struct Edge {
	int vex1;
	int vex2;
	int weight;
};

class CGraph {
public:
	void Init();
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	void ViewVex();
	void ViewEdge();
	Vex GetVex(int nVex);
	int GetEdge(int u, int v);
	int FindEdge(int nVex, Edge aEdge[]);
	int GetVexNum();
	void PrintPath(std::vector<int>& path);
	void DFS(int nVex, bool visited[], std::vector<int> &path);
	int FindShortPath(int start, int end);
	void FindMinTree();
	
private:
	int AdjMatrix[20][20];
	Vex Vexs[20];
	int VexNum;
};

#endif
