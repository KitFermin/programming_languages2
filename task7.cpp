#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > adj;  // список смежности
vector<bool> visited;     // массив для отметки посещенных вершин

// Функция для добавления ребра в граф
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Функция DFS
void DFS(int v) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (!visited[u])
            DFS(u);
    }
}

// Функция для проверки возможности добраться из каждой остановки до любой другой
bool isEverywhereReachable() {
    for (int i = 0; i < adj.size(); i++) {
        visited.assign(adj.size(), false);
        DFS(i);
        for (int j = 0; j < visited.size(); j++)
            if (!visited[j])
                return false;
    }
    return true;
}

// Функция для проверки выполнения предыдущего условия при удалении любого из маршрутов
bool isEverywhereReachableWithoutEdge() {
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            int temp = adj[i][j];
            adj[i].erase(adj[i].begin() + j);
            if (!isEverywhereReachable()) {
                adj[i].insert(adj[i].begin() + j, temp);  // восстанавливаем ребро
                return false;
            }
            adj[i].insert(adj[i].begin() + j, temp);  // восстанавливаем ребро
        }
    }
    return true;
}

int main() {
    int N = 5;  // количество остановок
    adj.assign(N, vector<int>());
    visited.assign(N, false);

    // Добавляем ребра в граф (маршруты между остановками)
    // addEdge(u, v) добавляет ребро между остановками u и v
    // Например, addEdge(0, 1) добавляет ребро между остановками 0 и 1

    // Проверяем возможность добраться из каждой остановки до любой другой
    if (isEverywhereReachable())
        cout << "Да, можно добраться из каждой остановки до любой другой" << endl;
    else
        cout << "Нет, нельзя добраться из каждой остановки до любой другой" << endl;

    // Проверяем выполнение предыдущего условия при удалении любого из маршрутов
    if (isEverywhereReachableWithoutEdge())
        cout << "Да, можно добраться из каждой остановки до любой другой даже при удалении любого из маршрутов" << endl;
    else
        cout << "Нет, нельзя добраться из каждой остановки до любой другой при удалении любого из маршрутов" << endl;

    return 0;
}
