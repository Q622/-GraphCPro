#include "Graph.h"
#include "Tourism.h"

int main() {
	int op;
	CTourism t;
	
	menu();
	while(1) {
		std::cout << "Please enter your option(0~5):";
		std::cin >> op;
		switch(op) {
		case 0:
			exit(0);
			break;
		
		case 1:
			t.CreateGraph();
			break;
			
		case 2:
			t.GetSpotInfo();
			break;
			
		case 3:
			t.TravelPath();
			break;
			
		case 4:
			t.FindShortPath();
			break;
			
		case 5:
			t.DesignPath();
			break;
			
		default:
			break;
		}
	}
	
	return 0;
}
