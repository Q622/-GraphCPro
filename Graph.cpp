#include "Graph.h"

void CGraph::Init() {
	VexNum = 0;
	memset(AdjMatrix, INF, sizeof(AdjMatrix));	
}

bool CGraph::InsertVex(Vex sVex) {
	if(VexNum == SIZE) return false;
	AdjMatrix[VexNum][VexNum] = 0;
	Vexs[VexNum].num = sVex.num;
	Vexs[VexNum].name = sVex.name;
	Vexs[VexNum++].info = sVex.info;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge) {
	if(sEdge.vex1 < 0 || sEdge.vex1 >= VexNum || sEdge.vex2 < 0 || sEdge.vex2 >= VexNum)
		return false;
	AdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	AdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

void CGraph::ViewVex(){
	for(int i = 0; i < VexNum; i++)
		std::cout << i << "-" << Vexs[i].name << std::endl;
}

void CGraph::ViewEdge(){
	for(int i = 0; i < VexNum; i++)
		for(int j = 0; j < VexNum; j++)
			std::cout << "<" << i << "," << j << "> " << AdjMatrix[i][j] << std::endl;
}

Vex CGraph::GetVex(int nVex) {
	if(nVex >= VexNum) exit(1);
	return Vexs[nVex];
}

int CGraph::GetEdge(int u, int v){
	return AdjMatrix[u][v];
}

int CGraph::FindEdge(int nVex, Edge aEdge[]) {
	int index = 0;
	for(int i = 0; i < VexNum; i++)
		if(AdjMatrix[nVex][i] != 0){
			aEdge[index].vex1 = nVex;
			aEdge[index].vex2 = i;
			aEdge[index++].weight = AdjMatrix[nVex][i];
		}
	return index;
}

int CGraph::GetVexNum() {
	return VexNum;	
}

void CGraph::PrintPath(std::vector<int>& path){
	for(int i = 0; static_cast<unsigned int>(i) < path.size(); i++){
		std::cout << Vexs[path[i]].name;
		if(static_cast<unsigned int>(i) != path.size() - 1) std::cout << "->";
	}
	std::cout << std::endl;
}

void CGraph::DFS(int nVex, bool visited[], std::vector<int> &path) {
	visited[nVex] = true;    
	path.push_back(nVex);    
	if(path.size() == static_cast<unsigned int>(VexNum)) PrintPath(path);
	else{
		for(int i = 0; i < VexNum; i++)
			if(AdjMatrix[nVex][i] != 0 && AdjMatrix[nVex][i] != INF && !visited[i])
				DFS(i, visited, path);
	}
	visited[nVex] = false;
	path.pop_back();
}

int CGraph::FindShortPath(int start, int end){
	int n = VexNum;
	int dist[20];
	bool visited[20];
	memset(dist, INF, sizeof(dist));
	memset(visited, false, sizeof(visited));
	dist[start] = 0;
	for(int i = 0; i < n; i++){
		int k = -1;
		for(int j = 0; j < n; j++)
			if(!visited[j] && (k == -1 || dist[j] < dist[k]))
				k = j;
		visited[k] = true;
		for(int j = 0; j < n; j++)
			if(!visited[j]) 
				dist[j] = std::min(dist[j], dist[k] + AdjMatrix[k][j]);
	}
	
	int p = end;
	int path[20];
	int count = 0;
	while(p != start){
		path[count++] = p;
		for(int i = 0; i < n; i++)
			if(AdjMatrix[p][i] != INF && dist[p] == dist[i] + AdjMatrix[p][i]){
				p = i;
				break;
			}
	}
	path[count] = start; 
	for(int i = count; i > 0; i--)
		std::cout << Vexs[path[i]].name << "->";
	std::cout << Vexs[path[0]].name << std::endl;
	return dist[end];
}

void CGraph::FindMinTree(){
	int n = VexNum;
	int dist[n];
	bool visited[n];
	Edge aEdge[n];
	int aPath[n];
	//记录下标
	int index1, index2;
	memset(dist, INF, sizeof(dist));
	memset(visited, false, sizeof(visited));
	//第一个顶点的初始化
	aPath[0] = 0;
	dist[0] = 0;
	visited[0] = true;
	//剩下n-1个顶点进行排序
	for(int i = 1; i < n; i++){
		int min = INF;
		for(int j = 0; j < i; j++){
			for(int k = 0; k < n; k++){
			if( this->AdjMatrix[aPath[j]][k] != 0 && this->AdjMatrix[aPath[j]][k] < min && visited[k] == false){
				min = this->AdjMatrix[j][k];
				index2 = k;
				index1 = aPath[j];
				}
			}
		}
		visited[index2] = true;
		aPath[i] = index2;
		aEdge[i-1].vex1 = index1;
		aEdge[i-1].vex2 = index2;
		aEdge[i-1].weight = this->AdjMatrix[index2][index1];
	}
	/**for(int i = 0; i < n; i++){
		int k = -1;
		for(int j = 0; j < n; j++)
			if(!visited[j] && (k == -1 || dist[j] < dist[k]))
				k = j;
		visited[k] = true;
		for(int j = 0; j < n; j++)
			if(!visited[j] && AdjMatrix[k][j] < dist[j]){
				dist[j] = AdjMatrix[k][j];
				aEdge[count].vex1 = k;
				aEdge[count].vex2 = j;
				aEdge[count].weight = AdjMatrix[k][j];
			} 
		count++;		
	  }**/
	
	int sum = 0;
	for(int i = 0; i < n-1; i++){
		std::cout << Vexs[aEdge[i].vex1].name << "-" << Vexs[aEdge[i].vex2].name << " " << aEdge[i].weight << "m" << std::endl;
		sum += aEdge[i].weight;
	}
	std::cout << sum << std::endl;
	
}
