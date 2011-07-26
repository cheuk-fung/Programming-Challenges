/*
 *  SRC: NKOJ p1667
 * PROB: Power Network
 * ALGO: Dinic
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

struct Edge {
    int v, p;
    int c, f; // capa, flow
};

const int INF = 0x3fffffff;
const int MAX_N = 110;
const int src = 0, dest = MAX_N;

Edge edge[MAX_N + 1][MAX_N + 1];
int dist[MAX_N + 1];

inline int min(int a, int b)
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
        for (int v = 1; v <= dest; v++)
            if (dist[v] == -1 && edge[u][v].f < edge[u][v].c) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
    }

    return dist[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (int v = 1; v <= dest; v++)
        if (dist[v] == dist[u] + 1 && edge[u][v].f < edge[u][v].c) {
            int tmp = dfs(v, min(f - res, edge[u][v].c - edge[u][v].f));
            res += tmp;
            edge[u][v].f += tmp;
            edge[v][u].f = -edge[u][v].f;
            if (res == f) break;
        }

    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        int tmp = dfs(src, MAX_N);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

inline void addEdge(int u, int v, int capa, int flow)
{
    edge[u][v].c += capa;
}

bool buildGraph()
{
    int n, np, nc, m;
    if (scanf("%d%d%d%d", &n, &np, &nc, &m) != 4) return false;

    memset(edge, 0, sizeof(edge));

    char s[100];
    int u, v, z;
    for (int i = 0; i < m; i++) {
        scanf("%*[^(](%d,%d)%d", &u, &v, &z);
        addEdge(u + 1, v + 1, z, 0);
    }

    for (int i = 0; i < np; i++) {
        scanf("%*[^(](%d)%d", &u, &z);
        addEdge(src, u + 1, z, 0);
    }

    for (int i = 0; i < nc; i++) {
        scanf("%*[^(](%d)%d", &u, &z);
        addEdge(u + 1, dest, z, 0);
    }

    return true;
}

int main()
{
    while (buildGraph())
        printf("%d\n", dinic());

    return 0;
}

