#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#include <time.h>


using namespace std;
typedef vector<pair<long, int>> Edges;

int main() {
    // clock_t t0 = clock();
    
    int size;
    cin >> size;
    
    while (size != 0) {
        vector<Edges> adjList(size);
        
        for (int i = 0; i < size - 1; i++) {
            int dest;
            long length;
            cin >> dest >> length;
            
            adjList[i + 1].push_back(make_pair(length, dest));
            adjList[dest].push_back(make_pair(length, i + 1));
        }
        
        int numTests;
        cin >> numTests;
        
        for (int i = 0; i < numTests; i++) {
            int src, dest;
            cin >> src >> dest;
            
            vector<bool> visited(adjList.size(), false);
            vector<long> dists(adjList.size(), 0);
            stack<int> s;
            s.push(src);
            
            while (!s.empty() && !visited[dest]) {
                int v = s.top();
                s.pop();
                           
                if (v == dest) {
                    visited[dest] = true;
                    cout << dists[dest] << " ";
                    
                } else if (!visited[v]) {
                    visited[v] = true;
                    for (int j = 0; j < adjList[v].size(); j++) {
                        pair<int, int> e = adjList[v][j];
                        s.push(e.second);
                        dists[e.second] = dists[v]
                                        + e.first;
                    }
                }
            }
        }
        
        cout << endl;
        cin >> size;
    }
    
    // clock_t tf = clock();
    // cout << (tf - t0) * 1000.0 / CLOCKS_PER_SEC << endl;
    return 0;
}
