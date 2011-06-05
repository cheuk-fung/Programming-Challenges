/*
 *  SRC: POJ
 * TASK: Dining
 * ALGO: dinic
 * DATE: 06/02/2011 
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

const int MAX = 1000;
const int src = 0, dest = MAX;

vector<Edge> edge[MAX + 1];
int dist[MAX + 1];

int N, F, D;

void init()
{
    scanf("%d%d%d", &N, &F, &D);

    /*
     * 0: src
     * 1 to F: FF
     * F + 1 to F + N: C1
     * F + N + 1 to F + 2N: C2
     * F + 2N + 1 to F + 2N + D: DD
     * MAX: dest
     */

    const int FF = 0;
    const int C1 = F, C2 = F + N;
    const int DD = F + 2 * N;

    for (int i = 1; i <= F; i++) {
        // src -> FF, capa = 1
        edge[src].push_back(Edge(FF + i, edge[FF + i].size(), 1, 0));
        // FF -> src, capa = 0
        edge[FF + i].push_back(Edge(src, edge[src].size() - 1, 0, 0));
    }
    for (int i = 1; i <= N; i++) {
        // C1 -> C2, capa = 1
        edge[C1 + i].push_back(Edge(C2 + i, edge[C2 + i].size(), 1, 0));
        // C2 -> C1, capa = 0
        edge[C2 + i].push_back(Edge(C1 + i, edge[C1 + i].size() - 1, 0, 0));
    }
    for (int i = 1; i <=D; i++) {
        // DD -> dest, capa = 1
        edge[DD + i].push_back(Edge(dest, edge[dest].size(), 1, 0));
        // dest -> DD, capa = 0
        edge[dest].push_back(Edge(DD + i, edge[DD + i].size() - 1, 0, 0));
    }

    for (int i = 1; i <= N; i++) {
        int f, d;
        scanf("%d%d", &f, &d);
        for (int j = 0; j < f; j++) {
            int tmp;
            scanf("%d", &tmp);
            // FF -> C1, capa = 1
            edge[FF + tmp].push_back(Edge(C1 + i, edge[C1 + i].size(), 1, 0));
            // C1 -> FF, capa = 0
            edge[C1 + i].push_back(Edge(FF + tmp, edge[FF + tmp].size() - 1, 0, 0));
        }
        for (int j = 0; j < d; j++) {
            int tmp;
            scanf("%d", &tmp);
            // C2 -> DD, capa = 1
            edge[C2 + i].push_back(Edge(DD + tmp, edge[DD + tmp].size(), 1, 0));
            // DD -> C2, capa = 0
            edge[DD + tmp].push_back(Edge(C2 + i, edge[C2 + i].size() - 1, 0, 0));
        }
    }
}

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
        int tmp = dfs(src, MAX);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

int main()
{
    init();

    int ans = dinic();

    printf("%d\n", ans);

    return 0;
}

