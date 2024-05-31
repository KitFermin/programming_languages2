#include <vector>
#include <iostream>

using namespace std;

class Graph {
    int V;
    vector< vector<int> > adj;
    vector<int> colorArr;
    bool isBipartite;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        colorArr.resize(V, 0);
        isBipartite = true;
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    // Рекурсивная реализация DFS
    void DFSUtil(int v, int color) {
        colorArr[v] = color;
        for (int i = 0; i < adj[v].size(); i++) {
            if (colorArr[adj[v][i]] == 0)
                DFSUtil(adj[v][i], 3 - color);
            else if (colorArr[adj[v][i]] == colorArr[v])
                isBipartite = false;
        }
    }

    // Нерекурсивная реализация DFS
    void DFS(int v) {
        vector<int> stack;
        stack.push_back(v);
        colorArr[v] = 1;

        while (!stack.empty()) {
            v = stack.back();
            stack.pop_back();

            for (vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i) {
                if (colorArr[*i] == 0) {
                    stack.push_back(*i);
                    colorArr[*i] = 3 - colorArr[v];
                }
                else if (colorArr[*i] == colorArr[v])
                    isBipartite = false;
            }
        }
    }

    // Проверка графа на двудольность
    bool checkBipartite() {
        DFS(0);
        return isBipartite;
    }
};


int main() {
    int V = 4;
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);

    if (g.checkBipartite())
        cout << "Граф является двудольным\n";
    else
        cout << "Граф не является двудольным\n";

    return 0;
}

