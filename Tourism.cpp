#include "Graph.h"
#include "Tourism.h"

void menu() {
	std::cout << "Scenic Information Management System" << std::endl;
	std::cout << "1.Create Graph" << std::endl;
	std::cout << "2.Query Spot Information" << std::endl;
	std::cout << "3.Navigate Tourism Spot" << std::endl;
	std::cout << "4.Search Shortest Path" << std::endl;
	std::cout << "5.Lay Circuit Planning" << std::endl;
	std::cout << "0.Exit" << std::endl;
}

void CTourism::CreateGraph() {	
	graph.Init();
	std::cout << "===== Create Scenic Spot Graph ====="  << std::endl;
	
	//构建顶点
	std::ifstream VexFile("vex.txt");
	if(!VexFile.is_open()){
		std::cout << "Failed to open \"vex.txt\"!" << std::endl;
		exit(1);
	}
	
	int n;
	Vex sVex;
	
	VexFile >> n;
	std::cout << "Vertex number:" << n << std::endl;
	std::cout << "----- Vertex -----" << std::endl;
	for(int i = 0; i < n; i++){
		VexFile >> sVex.num;
		VexFile >> sVex.name;
		VexFile >> sVex.info;
		if(!graph.InsertVex(sVex)){
			std::cout << "Failed to insert vex" << i << std::endl;
			exit(1);
		}
		std::cout << i << "-" << sVex.name << " ( " << sVex.info << " )" << std::endl;
	}
	VexFile.close();
	
	//构建边
	std::ifstream EdgeFile("edge.txt");
	if(!EdgeFile.is_open()){
		std::cout << "Failed to open \"edge.txt\"!" << std::endl;
		exit(1);
	}
	
	int count = 0, number;
	Edge sEdge;
	
	std::cout << "----- Edge -----" << std::endl;
	while(EdgeFile >> number){
		count++;
		switch(count % 3){
		case 1:
			sEdge.vex1 = number;
			break;
			
		case 2:
			sEdge.vex2 = number;
			break;
			
		case 0:
			sEdge.weight = number;
			if(!graph.InsertEdge(sEdge)){
				std::cout << "Failed to insert edge:" << "<" << sEdge.vex1 << ", " << sEdge.vex2 << "> " << sEdge.weight << std::endl;
				exit(1);
			}
			std::cout << "<" << sEdge.vex1 << ", " << sEdge.vex2 << "> " << sEdge.weight << std::endl;
			break;
		}
	}
	EdgeFile.close();
}

void CTourism::GetSpotInfo() {
	std::cout << "===== Query Spot Information =====" << std::endl;
	
	int n = graph.GetVexNum(), goal;
	graph.ViewVex();
	std::cout << "Please input the spot number you want to query:";
	std::cin >> goal;
	
	std::cout << "----- Spot Info -----" << std::endl;
	std::cout << graph.GetVex(goal).name << std::endl;
	std::cout << graph.GetVex(goal).info << std::endl;
	
	std::cout << "-----Spot Around -----" << std::endl;
	for(int i = 0; i < n; i++)
		if(graph.GetEdge(goal, i) > 0 && graph.GetEdge(goal, i) != INF)
			std::cout << graph.GetVex(goal).name << "->" << graph.GetVex(i).name << " " << graph.GetEdge(goal, i) << "m" <<std::endl;
}

void CTourism::TravelPath() {
	int goal;
	std::cout << "===== Navigate Tourism Spot =====" << std::endl;
	graph.ViewVex();
	std::cout << "Please input the original spot number:";
	std::cin >> goal;
	std::cout << "Tourist path:" << std::endl;
	
	bool visited[20];
	std::vector<int> path;
	memset(visited, false, sizeof(visited));
	graph.DFS(goal, visited, path);
}

void CTourism::FindShortPath() {
	int start, end, dist;
	std::cout << "===== Search Shortest Path =====" << std::endl;
	graph.ViewVex();
	std::cout << "Please input the number of origin:";
	std::cin >> start;
	std::cout << "Please input the number of destination:";
	std::cin >> end;
	std::cout << "The shortest path:" << std::endl;
	
	dist = graph.FindShortPath(start, end);
	std::cout << "The shortest distance:" << dist << std::endl;
}

void CTourism::DesignPath() {
	std::cout << "===== Lay Circuit Planning =====" << std::endl;
	std::cout << "Lay circuit between these spots:" << std::endl;
	graph.FindMinTree();
}
