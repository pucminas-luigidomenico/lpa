#include <algorithm>
#include <iostream>
#include <climits>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

enum SizeShirt {XXL=1, XL, L, M, S, XS};

class Graph {
public:
  Graph(int size);
  void add_edge(int from, int to, int weight);
  int max_flow(int source, int sink);
  void show() const;
  
private:
  vector<vector<int>> adj_matrix;
  bool BFS(int source, int sink, vector<int> &parent) const;
};

Graph::Graph(int size)
  : adj_matrix(size, vector<int>(size)) { }

void Graph::add_edge(int from, int to, int weight) {
  adj_matrix[from][to] = weight;
}

// Implemented with Edmonds-Karp algorithm
int Graph::max_flow(int source, int sink) {
  vector<int> parent(adj_matrix.size(), -1);
  int max_flow = 0;
  bool has_path = BFS(source, sink, parent);
  
  while (has_path) {
    int path_flow = INT_MAX;
    int u = sink;

    while (u != source) {
      path_flow = min(path_flow, adj_matrix[parent[u]][u]);
      u = parent[u];
    }

    max_flow += path_flow;

    u = sink;
    while (u != source) {
      int v = parent[u];
      adj_matrix[v][u] -= path_flow;
      adj_matrix[u][v] += path_flow;
      u = v;
    }
    
    has_path = BFS(source, sink, parent);
  }

  return max_flow;
}

bool Graph::BFS(int source, int sink, vector<int> &parent) const {
  vector<bool> visited(adj_matrix.size(), false);
  queue<int> queue;

  queue.push(source);
  visited[source] = true;

  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();

    for (int v = 0; v < adj_matrix[u].size(); v++) {
      if (!visited[v] && adj_matrix[u][v] > 0) {
        queue.push(v);
        visited[v] = true;
        parent[v] = u;
      }
    }
  }

  return visited[sink];
}

void Graph::show() const {
  for (auto &row : adj_matrix) {
    for (auto &col : row) {
      cout << col << " ";
    }
    cout << endl;
  }
}

int main() {
    unordered_map<string, int> size_map({{"XXL", XXL}, {"XL", XL},
                                         {"L", L}, {"M", M},
                                         {"S", S}, {"XS", XS}});
    
    int num_tests;
    cin >> num_tests;

    while (num_tests > 0) {
      int num_shirts, num_volunteers;
      cin >> num_shirts >> num_volunteers;

      // Graph: source, shirts, volunteers and sink
      int size_graph = 6 + num_volunteers + 2;
      int source = 0;
      int sink = size_graph - 1;

      // Graph as adjacency matrix
      Graph graph(size_graph);

      /**
       * Construct the edges from the source to the t-shirt nodes.
       * The capacity of these edges will be num_shirts/6.
       */
      for (int i = 0; i < 6; i++) {
        graph.add_edge(source, i + 1, num_shirts / 6);
      }

      /**
       * Construct the edges from the t-shirt nodes to the volunteers
       * nodes.
       */
      for (int i = 0; i < num_volunteers; i++) {
        string size1, size2;
        cin >> size1 >> size2;
      
        graph.add_edge(size_map[size1], i + 7, 1);
        graph.add_edge(size_map[size2], i + 7, 1);
      }

      /**
       * Construct the edges from the volunteer nodes to the
       * sink node.
       */
      for (int i = 0; i < num_volunteers; i++) {
        graph.add_edge(i + 7, sink, 1);
      }

      if (graph.max_flow(source, sink) == num_volunteers) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
      
      num_tests--;
    }
    return 0;
}
