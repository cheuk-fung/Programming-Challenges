/*
 *  SRC: POJ 3469
 * PROB: Dual Core CPU
 * ALGO: Dinic
 * DATE: Sep 09, 2011 
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

    Edge(int _v, int _p, int _c)
        : v(_v), p(_p), c(_c), f(0)
    { }
};

const int INF = 0x3fffffff;
const int MAX_N = 500000;
const int orig = 0, dest = MAX_N;

vector<Edge> edge[MAX_N + 1];
int lev[MAX_N + 1];

inline int fmin(int a, int b)
{
    return a < b ? a : b;
}

inline void add_edge(int u, int v, int capa)
{
    edge[u].push_back(Edge(v, edge[v].size(), capa));
    edge[v].push_back(Edge(u, edge[u].size() - 1, 0));
}

void build_graph()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(orig, i, a);
        add_edge(i, dest, b);
    }

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        add_edge(a, b, w);
        add_edge(b, a, w);
    }
}

bool bfs()
{
    memset(lev, -1, sizeof(lev));

    queue<int> Q;
    Q.push(orig);
    lev[orig] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (unsigned int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            if (lev[v] == -1 && edge[u][i].f < edge[u][i].c) {
                lev[v] = lev[u] + 1;
                Q.push(v);
            }
        }
    }

    return lev[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (unsigned int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i].v;
        if (lev[v] == lev[u] + 1 && edge[u][i].f < edge[u][i].c) {
            int tmp = dfs(v, fmin(f - res, edge[u][i].c - edge[u][i].f));
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
        int tmp = dfs(orig, MAX_N);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

int main()
{
    build_graph();

    printf("%d\n", dinic());

    return 0;
}

