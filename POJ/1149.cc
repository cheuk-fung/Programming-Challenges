/*
 *  SRC: POJ 1149
 * PROB: PIGS
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
const int MAX_N = 1111;
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

int m, n;
int pre[MAX_N];

void buildGraph()
{
    scanf("%d%d", &m, &n);

    for (int i = 1; i <= m; i++) {
        int pigs;
        scanf("%d", &pigs);
        addEdge(src, i, pigs, 0);
    }

    for (int i = 1; i <= n; i++) {
        int cnt;
        scanf("%d", &cnt);
        for (int j = 1; j <= cnt; j++) {
            int key;
            scanf("%d", &key);
            if (pre[key]) addEdge(pre[key], i + m, INF, 0);
            else addEdge(key, i + m, INF, 0);
            pre[key] = i + m;
        }

        scanf("%d", &cnt);
        addEdge(i + m, dest, cnt, 0);
    }
}

int main()
{
    buildGraph();

    printf("%d\n", dinic());

    return 0;
}


