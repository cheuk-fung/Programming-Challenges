/*
 *  SRC: POJ 2239
 * PROB: Selecting Courses
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

using std::vector;
using std::queue;

struct Edge {
    int v, p;
    int c, f; // capa, flow

    Edge(int vv, int pp, int cc, int ff)
        : v(vv), p(pp), c(cc), f(ff)
    { }
};

const int INF = 0x3fffffff;
const int MAX_N = 500;
const int src = 0, dest = MAX_N;

vector<Edge> edge[MAX_N + 1];
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
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            if (dist[v] == -1 && edge[u][i].f < edge[u][i].c) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }

    return dist[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i].v;
        if (dist[v] == dist[u] + 1 && edge[u][i].f < edge[u][i].c) {
            int tmp = dfs(v, min(f - res, edge[u][i].c - edge[u][i].f));
            res += tmp;
            edge[u][i].f += tmp;
            int j = edge[u][i].p;
            edge[v][j].f = -edge[u][i].f;
            if (res == f) break;
        }
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

void addEdge(int u, int v, int capa, int flow)
{
    edge[u].push_back(Edge(v, edge[v].size(), capa, flow));
    edge[v].push_back(Edge(u, edge[u].size() - 1, 0, 0));
}

bool buildGraph()
{
    int n;
    if (scanf("%d", &n) == EOF) return false;

    for (int i = 0; i <= MAX_N; i++)
        edge[i].clear();

    for (int i = 1; i <= n; i++)
        addEdge(src, i, 1, 0);

    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        for (int j = 0; j < t; j++) {
            int p, q;
            scanf("%d%d", &p, &q);
            addEdge(i, (p - 1) * 12 + q + n, 1, 0);
        }
    }

    for (int i = 1; i <= 7; i++)
        for (int j = 1; j <= 12; j++)
            addEdge((i - 1) * 12 + j + n, dest, 1, 0);

    return true;
}

int main()
{
    while (buildGraph())
        printf("%d\n", dinic());

    return 0;
}


