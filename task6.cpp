#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m;
vector< vector<char> > field;
vector< vector<bool> > visited;

void dfs(int x, int y) {
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && field[nx][ny] == '#') {
            dfs(nx, ny);
        }
    }
}

int main() {
    cin >> n >> m;
    field.resize(n, vector<char>(m));
    visited.resize(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> field[i][j];

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && field[i][j] == '#') {
                dfs(i, j);
                count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}
