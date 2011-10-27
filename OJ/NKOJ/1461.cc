/*
 *  SRC: NKOJ p1461
 * PROB: Sightseeing tour
 * ALGO: Dinic
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
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
const int MAX_N = 209;
const int src = 0, dest = MAX_N;

vector<Edge> edge[MAX_N + 1];
int lev[MAX_N + 1];

inline int min(int a, int b)
{
    return a < b ? a : b;
}

bool bfs()
{
    memset(lev, -1, sizeof(lev));

    queue<int> Q;
    Q.push(src);
    lev[src] = 0;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < edge[u].size(); i++) {
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
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i].v;
        if (lev[v] == lev[u] + 1 && edge[u][i].f < edge[u][i].c) {
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

int m, s;
int full;
int inDeg[MAX_N + 1], outDeg[MAX_N + 1];

bool buildGraph()
{
    memset(inDeg, 0, sizeof(inDeg));
    memset(outDeg, 0, sizeof(outDeg));
    for (int i = 0; i <= MAX_N; i++) edge[i].clear();
    full = 0;

    scanf("%d%d", &m, &s);
    for (int i = 0; i < s; i++) {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        if (x != y) {
            outDeg[x]++;
            inDeg[y]++;
            if (!d) addEdge(x, y, 1, 0);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (abs(outDeg[i] - inDeg[i]) & 1) return false;
        else {
            if (outDeg[i] == inDeg[i]) continue;
            if (outDeg[i] > inDeg[i]) {
                addEdge(src, i, (outDeg[i] - inDeg[i]) >> 1, 0);
                full += (outDeg[i] - inDeg[i]) >> 1;
            }
            else addEdge(i, dest, (inDeg[i] - outDeg[i]) >> 1, 0);
        }
    }

    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        if (buildGraph())
            puts(dinic() == full ? "possible" : "impossible");
        else puts("impossible");
    }

    return 0;
}

