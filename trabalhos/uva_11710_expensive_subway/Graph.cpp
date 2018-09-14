#include "DisjointSet.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <queue>
#include <set>
#include <stack>

namespace graph {
    Graph::Graph(std::size_t size, bool isDirected) 
            : adjacencyList(size) {
        this->isDirected = isDirected;
    }
    
    Graph::Graph(std::vector<AdjacentEdges> adjacencyList, bool isDirected) {
        this->adjacencyList = adjacencyList;
        this->isDirected = isDirected;
    }

    void Graph::appendEdge(int vertex, Edge edge) {
        this->adjacencyList[vertex].push_back(edge);
        
        if (!this->isDirected) {
            this->adjacencyList[edge.second]
                .push_back(std::make_pair(edge.first, vertex));
        }
    }

    std::vector<bool> Graph::dfs(Vertex start) const {
        std::vector<bool> visited(this->size());
        std::stack<Vertex> stack;
        
        // Push start vertex
        stack.push(start);
        
        // While stack isn't empty, pop a vertex and
        // verify if it has already been visited. 
        // If wasn't: 
        // 1st: mark as visited
        // 2nd: run into all the edges conected to this vertex and
        // push all the adjacent vertices to stack.
        while (!stack.empty()) {
            Vertex v = stack.top();
            stack.pop();
            
            if (!visited[v.first]) {
                visited[v.first] = true;
                
                AdjacentEdges list = v.second;
                const std::size_t listSize = list.size();
                for (size_t i = 0; i < listSize; i++) {
                    Vertex u = std::make_pair(
                        list[i].second, 
                        this->adjacencyList[list[i].second]
                    );
                        
                    stack.push(u);
                }
            }
        }
        
        return visited;
    }

    bool Graph::isConnected() const {
        bool isConnected = true;
        Vertex start = std::make_pair(0, this->adjacencyList[0]);
        std::vector<bool> visited = this->dfs(start);
        const std::size_t visitedSize = visited.size();
        
        for (size_t i = 0; i < visitedSize && isConnected; i++) {
            if (!visited[i]) {
                isConnected = false;
            }
        }
        
        return isConnected;
    }
    
    Graph Graph::kruskalMST() const {
        const std::size_t graphSize = this->size();
        
        // Initialize MST as an undirected graph because
        // both Prim and Kruskal algorithms works for undirected graphs.
        Graph mst(graphSize, false);
        
        // The first element of the pair is also a pair
        // containing the weight of the edge and the destination vertex.
        // The second element is the source vertex.
        std::vector<std::pair<Edge, int>> edges;

        for (std::size_t i = 0; i < graphSize; i++) {
            AdjacentEdges adj = this->adjacencyList[i];
            const std::size_t numEdges = adj.size();
            
            for (std::size_t j = 0; j < numEdges; j++) {
                edges.push_back(std::make_pair(adj[j], i));
            }
        }

        std::sort(edges.begin(), edges.end());
        
        // Create subsets for union-find data structure.
        disjointSet::DisjointSet disjointSet(graphSize);
    
        // An auxiliary variable to count the number of edges already inserted
        // into MST.
        std::size_t numEdges = 0;

        // An auxiliary index to the current smaller edge and total number of edges.
        std::size_t smallerEdge = 0;
        std::size_t totalEdges = edges.size();

        // The number of edges that MST will contain is the number of vertices
        // of the graph minus one.
        while (smallerEdge < totalEdges && numEdges < graphSize - 1) {

            // The current smallest edge.
            std::pair<Edge, int> nextEdge = edges[smallerEdge++];
            
            // Representative elements for source and destination vertices.
            int srcRoot = disjointSet.find(nextEdge.second);
            int destRoot = disjointSet.find(nextEdge.first.second);
            
            // If including this edge does't cause cycle,
            // include it in MST and increment the index for 
            // next edge.
            // PS: A cycle is found if both vertices are
            // already in the same set.
            if (srcRoot != destRoot) {
                Edge edge = std::make_pair(nextEdge.first.first, nextEdge.second);
                mst.appendEdge(nextEdge.second, edge);
                
                disjointSet.merge(srcRoot, destRoot);
                numEdges++;
            }
        }
        
        return mst;
    }

    Graph Graph::primMST(int start) const {
        const std::size_t graphSize = this->size();
        
        // Initialize MST as an undirected graph because
        // both Prim and Kruskal algorithms works for undirected graphs.
        Graph mst(graphSize, false);
        std::vector<bool> inMST(graphSize, false);
        std::size_t sizeMST = 0;
        
        std::priority_queue<
    	    std::pair<Edge, int>,
    	    std::vector<std::pair<Edge, int>>,
    	    std::greater<std::pair<Edge, int>>
    	> minHeap;
    	
    	// Put in the priority queue all the adjacent vertices 
    	// of the start vertex.
    	std::size_t numEdges = this->adjacencyList[start].size();
    	for (size_t i = 0; i < numEdges; i++) {
    	    minHeap.push(std::make_pair(
    	        this->adjacencyList[start][i], start)
    	    );
    	}
    	
    	// While min heap is not empty:
    	// 1st: Get the smallest edge (the edge with the smallest weight).
    	// 2nd: Check if at least one of the vertices connected by that
    	// edge isn't already in the MST (Minimum Spanning Tree).
    	// 3rd: Put in the priority queue all the adjacent vertices 
    	// of the destination vertex.
    	while (!minHeap.empty() && sizeMST < graphSize) {
    	    graph::Edge edge = minHeap.top().first;
    	    int from = minHeap.top().second;
    	    int to = edge.second;
    	    minHeap.pop();
    	    
    	    if (!inMST[from] || !inMST[to]) {
	            mst.appendEdge(from, edge);
    	        inMST[from] = true;
    	        inMST[to] = true;
    	        sizeMST++;
    	        
    	        numEdges = this->adjacencyList[to].size();
    	        for (size_t i = 0; i < numEdges; i++) {
    	            minHeap.push(std::make_pair(this->adjacencyList[to][i], to));
    	        }
    	    }
    	}
    	
    	return mst;
    }
}