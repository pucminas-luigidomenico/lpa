#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

typedef pair<int, int> Edge;
typedef vector<vector<int>> Graph;

/**
 * Algoritmo de Dijkstra para encontrar o menor caminho
 * de um vertice 0 ate um vertice N.
 * @param const Graph& matriz de adjacencia
 * @param vector<int>& custo de abastecimento por cidade 
 * @param int src
 * @param int T tanque de combustivel
 * @return vector<int> Vetor com os "pais" de cada vertice
 * no menor caminho
 */
vector<int> shortest_path(const Graph &graph,
                          const vector<int> &cost,
                          int src,
                          int T) {
    
    vector<int> prev = vector<int>(graph.size(), -1);
    vector<int> dist = vector<int>(graph.size(), INT_MAX);

    // Fila de prioridades composta de um par (peso, vertice)
    priority_queue<Edge, vector<Edge>, greater<Edge>> q;

    dist[src] = 0;
    q.push(make_pair(0, src));

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        for (int v = 0; v < graph[u].size(); v++) {
            // Se nao existir aresta, continue para
            // a proxima iteracao
            if (graph[u][v] == -1) {
                continue;
            }

            // Inclui o custo de abastecer na cidad de partida
            // como peso da aresta
            int path = dist[u] + (graph[u][v] * cost[u]);

            // Se a distancia entre as cidades for maior
            // que o suportado pelo tanque de combustivel,
            // nao e um caminho valido
            if (graph[u][v] <= T && dist[v] > path) {
                dist[v] = path;
                prev[v] = u;

                // Como a priority_queue (heap) nao implementaa
                // uma funcao para atualizar chaves, inserir o vertice
                // com a distancia atualizada
                q.push(make_pair(dist[v], v));
            }
        }
    }

    return prev;
}

int main() {
    int N, M, T;
    cin >> N >> M >> T;

    while (N != 0 || M != 0 || T != 0) {
        Graph graph(N, vector<int>(N, -1));
        vector<int> cost(N);
        
        for (int i = 0; i < M; i++) {
            int src, sink, dist;
            cin >> src >> sink >> dist;

            src--;
            sink--;

            graph[src][sink] = dist;
            graph[sink][src] = dist;
        }

        for (int i = 0; i < N; i++) {
            cin >> cost[i];
        }

        // Calcule os menos caminhos
        vector<int> paths = shortest_path(graph, cost, 0, T);

        // Use uma pilha para guardar o caminho entre
        // origem e destino (0 e N - 1) na ordem correta
        stack<int> s;
       
        // Se existir somente uma cidade, custo e zero
        if (N == 1) {
            cout << 0 << endl;
            
        // Se o "pai" da ultima cidade for -1,
        // nao existe um caminho valido
        } else if (paths[N - 1] == -1) {
            cout << -1 << endl;
        } else {
            int v = N - 1;
            while (v != - 1) {
                s.push(v);
                v = paths[v];
            }

            // Primeiro vertice do caminho
            int u = s.top();
            s.pop();

            int partial_t = T;
            int cost_total = 0;
            
            while (!s.empty()) {
                int v = s.top();
                s.pop();

                // Se nao for possivel ir para a proxima cidade,
                // porque todas as estradas demandam maior quantidade
                // de combustivel do que o tanque suporta, sair do
                // loop e considerar como impossivel
                if (graph[u][v] > T) {
                    cost_total = -1;
                    break;
                }

                // Se nivel do tanque atual nao for suficiente
                // para viajar pela estrada (u, v), abastecer
                if (partial_t < graph[u][v]) {
                    // Abastecer o suficiente para a proxima cidade
                    int fuel = graph[u][v] - partial_t;
                    partial_t += fuel;
                    cost_total += fuel * cost[u];

                    // Abastecer o maximo possivel, enquanto o posto
                    // da cidade atual for o mais barato
                    stack<int> aux = s;
                    int x = u;
                    int y = v;

                    while (!aux.empty() && cost[x] < cost[y]) {
                        int z = aux.top();
                        aux.pop();

                        fuel = graph[y][z];
                        partial_t += fuel;

                        // Se distancia for maior que a quantidade
                        // que o tanque suporta, encher o tanque
                        // ate o limite
                        if (partial_t > T) {
                            fuel = T - partial_t;
                            partial_t += fuel;
                        }
                        cost_total += fuel * cost[x];
                        
                        y = z;
                    }
                }
                
                partial_t -= graph[u][v];
                u = v;
            }

            cout << cost_total << endl;
        }
        
        cin >> N >> M >> T;
    }
    return 0;
}
