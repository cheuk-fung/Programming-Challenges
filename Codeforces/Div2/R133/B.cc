#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

vector<int> e[101];
set<int> team[2], fteam[2];
int vis[101];

void dfs(int u, int x)
{
    for (int i = 0; i < SIZE(e[u]); i++) {
        int v = e[u][i];
        if (vis[v]) continue;
        vis[v] = true;
        bool ok = true;
        for (int j = 0; j < SIZE(e[v]); j++) {
            if (team[x ^ 1].count(e[v][j])) ok = false;
        }
        if (ok) {
            team[x ^ 1].insert(v);
            dfs(v, x ^ 1);
        }
    }
}

void join(const set<int> &orig, set<int> &dest)
{
    for (set<int>::iterator it = orig.begin(); it != orig.end(); it++) {
        dest.insert(*it);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            team[0].clear();
            team[1].clear();
            team[0].insert(i);
            dfs(i, 0);
            if (abs((SIZE(team[0]) + SIZE(fteam[0])) - (SIZE(team[1]) + SIZE(fteam[1]))) <= abs((SIZE(team[0]) + SIZE(fteam[1])) - (SIZE(team[1]) + SIZE(fteam[0])))) {
                join(team[0], fteam[0]);
                join(team[1], fteam[1]);
            } else {
                join(team[0], fteam[1]);
                join(team[1], fteam[0]);
            }
        }
    }

    int r = n - SIZE(fteam[0]) - SIZE(fteam[1]) + abs(SIZE(fteam[0]) - SIZE(fteam[1]));
    cout << r << endl;

    return 0;
}

