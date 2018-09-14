#include "Graph.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <string>

int main() {
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	
	int numStations, numConnections;
	std::cin >> numStations >> numConnections;
	
	while (numStations != 0 || numConnections != 0) {
	    std::map<std::string, int> stations;
    	graph::Graph graph(numStations, false);
    	
    	for (int i = 0; i < numStations; i++) {
    	    std::string station;
    	    std::cin >> station;
    	    
    	    stations.insert(std::make_pair(station, i));
    	}
    	
    	for (int i = 0; i < numConnections; i++) {
    	    std::string from, to;
    	    int weight;
    	    
    	    std::cin >> from >> to >> weight;
    	    graph.appendEdge(stations[from], std::make_pair(weight, stations[to]));
    	}
    	
    	std::string startStation;
    	std::cin >> startStation;
    	
        if (graph.isConnected()) {
    	   // graph::Graph mst = graph.primMST(stations[startStation]);
    	    graph::Graph mst = graph.kruskalMST();
    	   
    	    int weightMst = 0;
    	    const std::size_t sizeMST = mst.size();
    	   
    	    for (std::size_t i = 0; i < sizeMST; i++) {
    	        const std::size_t numEdges = mst[i].size();
    	       
    	        for (std::size_t j = 0; j < numEdges; j++) {
    	            weightMst += mst[i][j].first;
    	        }
            }
    	   
    	    // Since it's an undirected graph, the weight of each edge
    	    // was counted twice.
    	    weightMst /= 2;
    	    std::cout << weightMst << std::endl;
    	    
    	} else {
    	    std::cout << "Impossible" << std::endl;
    	}
    
    	std::cin >> numStations >> numConnections;
	}
	
	return 0;
}