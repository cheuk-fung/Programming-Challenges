/*
 *  SRC: POJ 3281
 * PROB: Dining
 * ALGO: Dinic
 * DATE: Jun 2, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::min;

const int INF = 0x3f3f3f3f;
const int MAXN = 1000;
const int orig = 0, dest = MAXN;

struct Edge {
    int v;
    int rev; // the position of revese edge
    int c, f; // capa, flow

    Edge(int _v, int _rev, int _c)
        : v(_v), rev(_rev), c(_c), f(0)
    { }
};
vector<Edge> edge[MAXN + 1];

int lev[MAXN + 1];

inline void add_edge(int u, int v, int capa)
{
    edge[u].push_back(Edge(v, edge[v].size(), capa));
    edge[v].push_back(Edge(u, edge[u].size() - 1, 0));
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

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
            int tmp = dfs(v, min(f - res, edge[u][i].c - edge[u][i].f));
            res += tmp;
            edge[u][i].f += tmp;
            int j = edge[u][i].rev;
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
        int tmp = dfs(orig, MAXN);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

void build_graph()
{
    int N, F, D;
    scanf("%d%d%d", &N, &F, &D);

    /*
     * 0: orig
     * 1 to F: FF
     * F + 1 to F + N: C1
     * F + N + 1 to F + 2N: C2
     * F + 2N + 1 to F + 2N + D: DD
     * MAXN: dest
     */

    const int FF = 0;
    const int C1 = F, C2 = F + N;
    const int DD = F + 2 * N;

    for (int i = 1; i <= F; i++) {
        // orig -> FF, capa = 1
        // FF -> orig, capa = 0
        add_edge(orig, FF + i, 1);
    }
    for (int i = 1; i <= N; i++) {
        // C1 -> C2, capa = 1
        // C2 -> C1, capa = 0
        add_edge(C1 + i, C2 + i, 1);
    }
    for (int i = 1; i <=D; i++) {
        // DD -> dest, capa = 1
        // dest -> DD, capa = 0
        add_edge(DD + i, dest, 1);
    }

    for (int i = 1; i <= N; i++) {
        int f, d;
        scanf("%d%d", &f, &d);
        for (int j = 0; j < f; j++) {
            int tmp;
            scanf("%d", &tmp);
            // FF -> C1, capa = 1
            // C1 -> FF, capa = 0
            add_edge(FF + tmp, C1 + i, 1);
        }
        for (int j = 0; j < d; j++) {
            int tmp;
            scanf("%d", &tmp);
            // C2 -> DD, capa = 1
            // DD -> C2, capa = 0
            add_edge(C2 + i, DD + tmp, 1);
        }
    }
}

int main()
{
    build_graph();

    printf("%d\n", dinic());

    return 0;
}
