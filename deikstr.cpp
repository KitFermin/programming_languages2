#include <vector>
#include <iostream>

using namespace std;

#define INF 1000000

class Graph {
public:
    Graph(int vertices) : vertices_(vertices), adjacency_matrix_(vertices, vector<int>(vertices, INF)) {}

    void addEdge(int u, int v, int weight) {
        adjacency_matrix_[u][v] = weight;
        adjacency_matrix_[v][u] = weight;
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(vertices_, INF);
        vector<bool> visited(vertices_, false);

        dist[src] = 0;

        for (int count = 0; count < vertices_ - 1; ++count) {
            int u = minDistance(dist, visited);
            visited[u] = true;

            for (int v = 0; v < vertices_; ++v) {
                if (!visited[v] && adjacency_matrix_[u][v] && dist[u] != INF && dist[u] + adjacency_matrix_[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacency_matrix_[u][v];
                }
            }
        }

        return dist;
    }

private:
    int minDistance(const vector<int>& dist, const vector<bool>& visited) {
        int min = INF, min_index;

        for (int v = 0; v < vertices_; ++v) {
            if (visited[v] == false && dist[v] <= min) {
                min = dist[v], min_index = v;
            }
        }

        return min_index;
    }

    int vertices_;
    vector< vector<int> > adjacency_matrix_;
};

int main() {
    Graph g(5);

    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);
    g.addEdge(2, 3, 20);
    g.addEdge(3, 4, 25);
    g.addEdge(4, 0, 30);

    vector<int> dist = g.dijkstra(0);

    for (int i = 0; i < dist.size(); ++i) {
        cout << "Distance from node 0 to node " << i << " is " << dist[i] << endl;
    }

    return 0;
}
