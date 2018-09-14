#include <vector>
#include <ostream>
#include <utility>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <iostream>
#include <map>
#include <string>

namespace disjointSet {
    /** 
     * A structure to represent a subset for union-find.
     */
    struct Subset {
        int parent;
        int rank;
    };
    
    class DisjointSet {
    public:
        /**
         * Constructor with single parameter that initializes
         * the subset vector according with the maximum number
         * of subsets.
         * 
         * @param std::size_t The maximum number of subsets
         */
        DisjointSet(std::size_t maxNumber);
    
         /**
         * Finds the representive member of the set to which
         * element x belongs, and may be x itself.
         * 
         * Uses path compression as an optimization.
         * 
         * @param int the element we are looking for
         * @return int The representive member of the set to which
         * element x belongs.
         */
        int find(int x);
        
        /**
         * Union function that uses find to determine the roots of
         * the trees x and y belong to. If the roots are distinct,
         * the trees are combined by attaching the root of one to  
         * the root of the other.
         * 
         * Uses union by rank as an optimization.
         *
         * @param int one of the elements that gonna has its subset
         * merged.
         * @param int the other element that gonna has its subset
         * merged.
         */
        void merge(int x, int y);
        
    private:
        std::vector<Subset> subsets;
    };

    DisjointSet::DisjointSet(std::size_t maxNumber)
        : subsets(maxNumber) { 
    
        for (std::size_t i = 0; i < maxNumber; i++) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }
    }
        
    int DisjointSet::find(int x) {
        if (subsets[x].parent != x) {
            subsets[x].parent = find(subsets[x].parent);
        }
        
        return subsets[x].parent;
    }
    
    void DisjointSet::merge(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        
        if (xRoot == yRoot) {
            return;
        }
        
        if (subsets[xRoot].rank < subsets[yRoot].rank) {
            subsets[xRoot].parent = yRoot;
        } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
            subsets[yRoot].parent = xRoot;
        } else {
            subsets[xRoot].parent = yRoot;
            subsets[yRoot].rank++;
        }
    }
}

namespace graph {
    // The first item of the edge is its weight.
    // The second item of the edge is the destination vertex.
    typedef std::pair<int, int> Edge;
    
    // List of adjacent edges.
    typedef std::vector<Edge> AdjacentEdges;
    
    // The first item of the vertex is the vertex itself.
    // The second item of the vertex is a list of all connected
    // edges.
    typedef std::pair<int, AdjacentEdges> Vertex;
    
    class Graph {
    public:
        /** 
         * Constructor with single parameter that initializes
         * the adjacency list with an specific size.
         * 
         * @param std::size_t Number of vertices
         * @param bool Is a directed graph?
         * @return Graph
         */
        Graph(std::size_t size, bool isDirected);
        
        /** 
         * Constructor with single parameter that receives
         * an already built adjacency list.
         * 
         * @param std::vector<AdjacentEdges> Adjacency list
         * @param bool Is a directed graph?
         * @return Graph
         */
        Graph(std::vector<AdjacentEdges> adjacencyList, bool isDirected);
        
        /**
         * Append an edge to the graph in both directions (append
         * to both vertices).
         * 
         * @param int Origin vertex
         * @param Edge Pair formed by weight 
         * and destination vertex
         */
        void appendEdge(int vertex, Edge edge);

        /**
         * Determines whether a graph is connected or not,
         * using depth-first search to visit vertices.
         */
        bool isConnected() const;
        
        /**
         * Builds a minimum spanning tree using Kruskal's algorithm.
         * This algorithm uses a union-find data structure to help
         * determine whether adding an edge to the MST will result
         * in a cycle or not.
         * 
         * @return Graph that represents the minimum spanning tree
         */
        Graph kruskalMST() const;
        
        /**
         * Builds a minimum spanning tree using Prim's algorithm and
         * assuming that this graph is connected.
         * 
         * @param int Start vertex
         * @return Graph that represents the minimum spanning tree
         */
        Graph primMST(int start) const;
        
        /**
         * Returns the number of vertices in the graph.
         * 
         * @return std::size_t Number of vertices
         */
        std::size_t size() const {
            return this->adjacencyList.size();
        }
    
        /**
         * Overloaded bracket operator that allows one to modify 
         * this graph in the form of <variable_name[vertex_index]...>
         * 
         * @param std::size_t index
         * @return AdjacentEdges& Reference to the list of adjacent edges
         */
        AdjacentEdges &operator [](std::size_t i) {
            return this->adjacencyList[i];
        }
        
        /**
         * Overloaded bracket operator that allows one to read 
         * this graph in the form of <variable_name[vertex_index]>
         * 
         * @param std::size_t index
         * @return AdjacentEdges
         */
        AdjacentEdges operator [](std::size_t i) const {
            return this->adjacencyList[i];
        }
        
    private:
        // Boolean value to determine whether the graph is
        // isDirected or not.
        bool isDirected;
    
        // Vector of vertices that represents 
        // a list of adjacencies.
        std::vector<AdjacentEdges> adjacencyList;
        
        /**
         * Iterative depth-first search (using a stack), used
         * as an auxiliar function to determine whether a
         * graph is connected or not.
         * 
         * @param Vertex start vertex
         */
        std::vector<bool> dfs(Vertex start) const;
    };

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
        std::vector<std::pair<Edge, int> > edges;

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
    	    std::vector<std::pair<Edge, int> >,
    	    std::greater<std::pair<Edge, int> >
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

int main() {
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
    	
        // This approach works fine, but is slow because we're doing dfs every time to check
        // whether the graph is connected or not.

        // if (graph.isConnected()) {
    	//    // graph::Graph mst = graph.primMST(cities[startStation]);
		// 	graph::Graph mst = graph.kruskalMST();
			
		// 	int minCarRange = 0;
		// 	std::size_t mstSize = mst.size();
		// 	for (std::size_t i = 0; i < mstSize; i++) {
		// 		std::size_t numEdges = mst[i].size();

		// 		for (std::size_t j = 0; j < numEdges; j++) {
		// 			minCarRange = mst[i][j].first > minCarRange ? mst[i][j].first : minCarRange;
		// 		}
		// 	}

		// 	std::cout << minCarRange << std::endl;
    	// } else {
    	//     std::cout << "IMPOSSIBLE" << std::endl;
    	// }

        // Thus, instead of using that, we can use the kruskal algorithm directly here
        // and check if we got all the vertices. If so, than the graph is connected.
        // Graph's isConnected() method is still useful if we just need to check the
        // connectness of the graph. We're doing this just in order to get better running time.
        const std::size_t graphSize = graph.size();
        
        // Initialize MST as an undirected graph because
        // both Prim and Kruskal algorithms works for undirected graphs.
        graph::Graph mst(graphSize, false);
        
        // The first element of the pair is also a pair
        // containing the weight of the edge and the destination vertex.
        // The second element is the source vertex.
        std::vector<std::pair<graph::Edge, int> > edges;

        for (std::size_t i = 0; i < graphSize; i++) {
            graph::AdjacentEdges adj = graph[i];
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

        // An auxiliary variable to minimum range of the car.
        int minCarRange = 0;

        // The number of edges that MST will contain is the number of vertices
        // of the graph minus one.
        while (smallerEdge < totalEdges && numEdges < graphSize - 1) {

            // The current smallest edge.
            std::pair<graph::Edge, int> nextEdge = edges[smallerEdge++];
            
            // Representative elements for source and destination vertices.
            int srcRoot = disjointSet.find(nextEdge.second);
            int destRoot = disjointSet.find(nextEdge.first.second);
            
            // If including this edge does't cause cycle,
            // include it in MST and increment the index for 
            // next edge.
            // PS: A cycle is found if both vertices are
            // already in the same set.
            if (srcRoot != destRoot) {
                graph::Edge edge = std::make_pair(nextEdge.first.first, nextEdge.second);
                mst.appendEdge(nextEdge.second, edge);
                
                disjointSet.merge(srcRoot, destRoot);
                numEdges++;

                minCarRange = std::max(minCarRange, nextEdge.first.first);
            }
        }

        if (numEdges == graphSize - 1) {
            std::cout << minCarRange << std::endl;
        } else {
            std::cout << "IMPOSSIBLE" << std::endl;
        }

    	std::cin >> numCities >> numRoads;
	}
	
	return 0;
}