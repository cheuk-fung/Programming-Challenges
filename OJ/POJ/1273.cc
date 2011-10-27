/*
 *  SRC: POJ 1273
 * PROB: Drainage Ditches
 * ALGO: Dinic
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::queue;

struct Edge {
    long long c, f; // capa, flow
};

const long long INF = 0x3fffffffffffffffLL;
const int MAX_N = 210;
int src, dest;
int n;

Edge edge[MAX_N][MAX_N];
long long dist[MAX_N];

inline long long min(long long a, long long b)
{
    return a < b ? a : b;
}

bool bfs()
{
    memset(dist, -1, sizeof(dist));

    queue<int> Q;
    Q.push(src);
    dist[src] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v = 1; v <= n; v++)
            if (edge[u][v].c || edge[v][u].c) {
                if (dist[v] == -1 && edge[u][v].f < edge[u][v].c) {
                    dist[v] = dist[u] + 1;
                    Q.push(v);
                }
            }
    }

    return dist[dest] > -1;
}

long long dfs(int u, long long f)
{
    if (u == dest) return f;

    long long res = 0;
    for (int v = 1; v <= n; v++)
        if (edge[u][v].c || edge[v][u].c) {
            if (dist[v] == dist[u] + 1 && edge[u][v].f < edge[u][v].c) {
                long long tmp = dfs(v, min(f - res, edge[u][v].c - edge[u][v].f));
                res += tmp;
                edge[u][v].f += tmp;
                edge[v][u].f = -edge[u][v].f;
                if (res == f) break;
            }
        }

    return res;
}

long long dinic()
{
    long long res = 0;
    while (bfs()) {
        long long tmp = dfs(src, INF);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

bool buildGraph()
{
    int m;
    if (scanf("%d%d", &m, &n) == EOF) return false;

    src = 1;
    dest = n;

    memset(edge, 0, sizeof(edge));

    for (int i = 0; i < m; i++) {
        int s, e, c;
        scanf("%d%d%d", &s, &e, &c);
        if (s != e) edge[s][e].c += c;
    }

    return true;
}

int main()
{
    while (1 + 1 == 2) {
        if (!buildGraph()) break;

        printf("%lld\n", dinic());
    }

    return 0;
}
