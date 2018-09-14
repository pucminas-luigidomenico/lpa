#include "Graph.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <string>

int main() {
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	
	int numCities, numRoads;
	std::cin >> numCities >> numRoads;
	
	while (numCities != 0 || numRoads != 0) {
    	graph::Graph graph(numCities, false);
    	
    	for (int i = 0; i < numRoads; i++) {
    	    int from, to;
    	    int weight;
    	    
    	    std::cin >> from >> to >> weight;
    	    graph.appendEdge(from, std::make_pair(weight, to));
    	}
		
        if (graph.isConnected()) {
    	   // graph::Graph mst = graph.primMST(cities[startStation]);
			graph::Graph mst = graph.kruskalMST();
			
			int minCarRange = 0;
			std::size_t mstSize = mst.size();
			for (std::size_t i = 0; i < mstSize; i++) {
				std::size_t numEdges = mst[i].size();

				for (std::size_t j = 0; j < numEdges; j++) {
					minCarRange = mst[i][j].first > minCarRange ? mst[i][j].first : minCarRange;
				}
			}

			std::cout << minCarRange << std::endl;
    	} else {
    	    std::cout << "IMPOSSIBLE" << std::endl;
    	}
    
    	std::cin >> numCities >> numRoads;
	}
	
	return 0;
}