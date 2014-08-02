/*
 *  SRC: HDOJ 4085
 * PROB: Peach Blossom Spring
 * ALGO: Steiner tree
 * DATE: Sep 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 55;

struct Edge {
    int v, d;
};
vector<Edge> e[MAXN];

queue<int> que;
int ns[MAXN], f[1 << 10][MAXN], g[1 << 10];
int inque[1 << 10][MAXN];

void spfa()
{
    while (!que.empty()) {
        int s = que.front() / MAXN, u = que.front() % MAXN;
        que.pop();
        inque[s][u] = false;

        for (int i = 0; i < (int)e[u].size(); i++) {
            int v = e[u][i].v;
            int d = e[u][i].d;
            if (f[s][u] + d < f[s | ns[v]][v]) {
                f[s | ns[v]][v] = f[s][u] + d;
                if (s == (s | ns[v]) && !inque[s][v]) {
                    que.push(s * MAXN + v);
                    inque[s][v] = true;
                }
            }
        }
    }
}

void steiner_tree(int n, int k)
{
    for (int i = 0; i < 1 << k; i++) {
        for (int j = 0; j < n; j++) {
            for (int s = i & (i - 1); s; s &= s - 1) {
                f[i][j] = min(f[i][j], f[s | ns[j]][j] + f[(i - s) | ns[j]][j]);
            }
            if (f[i][j] < INF) {
                que.push(i * MAXN + j);
                inque[i][j] = true;
            }
        }
        spfa();
    }
}

bool check(int s, int k)
{
    int cnt = 0;
    for (int i = 0; i < k; i++) {
        if (s & (1 << i)) cnt++;
        if (s & (1 << (k + i))) cnt--;
    }
    return cnt == 0;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(ns, 0, sizeof ns);
        memset(f, 0x3f, sizeof f);
        memset(g, 0x3f, sizeof g);

        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) e[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            u--; v--;
            e[u].push_back((Edge){v, d});
            e[v].push_back((Edge){u, d});
        }

        for (int i = 0; i < k; i++) {
            ns[i] = 1 << i;
            f[ns[i]][i] = 0;
            ns[n - k + i] = 1 << (k + i);
            f[ns[n - k + i]][n - k + i] = 0;
        }
        steiner_tree(n, k << 1);

        int final = 1 << (k << 1);
        for (int i = 0; i < final; i++) {
            for (int j = 0; j < n; j++) {
                g[i] = min(g[i], f[i][j]);
            }
        }
        for (int i = 0; i < final; i++) {
            if (!check(i, k)) continue;
            for (int s = i & (i - 1); s; s = (s - 1) & i) {
                if (!check(s, k)) continue;
                g[i] = min(g[i], g[s] + g[i - s]);
            }
        }
        if (g[final - 1] == INF) puts("No solution");
        else printf("%d\n", g[final - 1]);
    }

    return 0;
}

