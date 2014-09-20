#include <iostream>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

int mat[110][110];
int vis[110];
pii drift[110];

void floodfill(int u, int n)
{
    if (vis[u]) return ;
    vis[u] = true;
    for (int v = 0; v < n; v++) {
        if (mat[u][v]) floodfill(v, n);
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> drift[i].first >> drift[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (drift[j].first == drift[i].first || drift[j].second == drift[i].second) {
                mat[i][j] = 1;
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cnt++;
            floodfill(i, n);
        }
    }

    cout << cnt - 1 << endl;

    return 0;
}

