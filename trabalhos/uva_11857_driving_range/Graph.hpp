#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <ostream>
#include <utility>
#include <vector>

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
}

#endif