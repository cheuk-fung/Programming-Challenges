/*
 *  SRC: POJ 2135
 * PROB: Farm Tour
 * ALGO: MCMF
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

inline int fmin(int a, int b) { return a < b ? a : b; }

const int INF = 0x3f3f3f3f;
const int MAX_N = 1010;
const int orig = 0, dest = MAX_N;

struct Edge {
    int v;
    int rev; // the position of revese edge
    int c, f; // capa, flow
    int cpf; // cost per flow

    Edge(int _v, int _rev, int _c, int _cpf)
        : v(_v), rev(_rev), c(_c), f(0), cpf(_cpf)
    { }
};
vector<Edge> edge[MAX_N + 1];

struct Route {
    int u, v, which;

    Route(int _u = 0, int _v = 0, int _which = 0)
        : u(_u), v(_v), which(_which)
    { }
};
Route bfs_route[MAX_N + 1];
bool vis[MAX_N + 1];
int dist[MAX_N + 1];

inline void add_edge(int u, int v, int capa, int cpf)
{
    edge[u].push_back(Edge(v, edge[v].size(), capa, cpf));
    edge[v].push_back(Edge(u, edge[u].size() - 1, 0, -cpf));
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    queue<int> Q;
    Q.push(orig);
    vis[orig] = true;
    dist[orig] = 0;
    bfs_route[orig] = Route(-1, 0, -1);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for (unsigned int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v,
                cpf = edge[u][i].cpf;
            if (cpf + dist[u] < dist[v] && edge[u][i].f < edge[u][i].c) {
                dist[v] = cpf + dist[u];
                bfs_route[v] = Route(u, v, i);
                if (vis[v] == false) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }

    return dist[dest] < INF;
}

int flow()
{
    int min_flow = INF;
    Route *r = &bfs_route[dest];
    while (r->u != -1) {
        min_flow = fmin(min_flow, edge[r->u][r->which].c - edge[r->u][r->which].f);
        r = &bfs_route[r->u];
    }

    int res = 0;
    r = &bfs_route[dest];
    while (r->u != -1) {
        edge[r->u][r->which].f += min_flow;
        res += edge[r->u][r->which].cpf;
        int j = edge[r->u][r->which].rev;
        edge[r->v][j].f = -edge[r->u][r->which].f;
        r = &bfs_route[r->u];
    }
    res *= min_flow;

    return res;
}

int mcmf()
{
    int res = 0;
    while (spfa()) res += flow();

    return res;
}

void build_graph()
{
    int n, m;
    scanf("%d%d", &n, &m);
    add_edge(orig, 1, 2, 0);
    for (int i = 0; i < m; i++) {
        int s, e, v;
        scanf("%d%d%d", &s, &e, &v);
        add_edge(s, e, 1, v);
        add_edge(e, s, 1, v);
    }
    add_edge(n, dest, 2, 0);
}

int main()
{
    build_graph();

    printf("%d\n", mcmf());

    return 0;
}
