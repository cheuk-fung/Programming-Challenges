/*
 *  SRC: POJ 2516
 * PROB: Minimum Cost
 * ALGO: MCMF
 * DATE: Jun 3, 2011 
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
    int cpf; // cost per flow

    Edge(int vv, int pp, int cc, int ff, int cost)
        : v(vv), p(pp), c(cc), f(ff), cpf(cost)
    { }
};

const int INF = 0x7fffffff;
const int MAXN = 200;
const int src = 0, dest = MAXN;

vector<Edge> edge[MAXN + 1];

struct Route {
    int u, v, p;

    Route(int uu = 0, int vv = 0, int pp = 0)
        : u(uu), v(vv), p(pp)
    { }
} aRoute[MAXN + 1];

bool vis[MAXN + 1];
int lowest[MAXN + 1];

inline int min(int a, int b)
{
    return a < b ? a : b;
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    for (int i = 0; i <= MAXN; i++) lowest[i] = INF;

    queue<int> Q;
    Q.push(src);
    vis[src] = true;
    lowest[src] = 0;
    aRoute[src] = Route(-1, 0, -1);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            int dis = edge[u][i].cpf;
            if (dis + lowest[u] < lowest[v] && edge[u][i].f < edge[u][i].c) {
                lowest[v] = dis + lowest[u];
                aRoute[v] = Route(u, v, i);
                if (vis[v] == false) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }

    return lowest[dest] < INF;
}

int flow()
{
    int minFlow = INF;
    Route r = aRoute[dest];
    while (r.u != -1) {
        minFlow = min(minFlow, edge[r.u][r.p].c - edge[r.u][r.p].f);
        r = aRoute[r.u];
    }

    int res = 0;
    r = aRoute[dest];
    while (r.u != -1) {
        edge[r.u][r.p].f += minFlow;
        res += edge[r.u][r.p].cpf;
        int j = edge[r.u][r.p].p;
        edge[r.v][j].f = -edge[r.u][r.p].f;
        r = aRoute[r.u];
    }
    res *= minFlow;

    return res;
}

int mcmf()
{
    int res = 0;
    while (spfa()) res += flow();

    return res;
}

void addEdge(int u, int v, int capa, int flow, int cpf)
{

    edge[u].push_back(Edge(v, edge[v].size(), capa, flow, cpf));
    edge[v].push_back(Edge(u, edge[u].size() - 1, 0, 0, -cpf));
}

int N, M, K;
int orders[60][60], storage[60][60], dist[60][60][60];

bool init()
{
    scanf("%d%d%d", &N, &M, &K);
    if (N == 0 && M == 0 && K == 0) return false;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= K; j++)
            scanf("%d", &orders[i][j]);

    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= K; j++)
            scanf("%d", &storage[i][j]);

    for (int k = 1; k <= K; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                scanf("%d", &dist[k][i][j]);

    return true;
}

void buildEdge(int k)
{
    /*
     * 0: src
     * 1 to M: Storage
     * M + 1 to M + N: Shopkeeper
     * MAXN: dest
     */

    const int  St = 0, SK = M;
    for (int i = 0; i <= M + N; i++) edge[i].clear();
    edge[dest].clear();

    for (int i = 1; i <= M; i++) {
        // src -> St, capa = storage[i][k], cpf = 0
        // St -> src, capa = 0, cpf = 0
        addEdge(src, St + i, storage[i][k], 0, 0);
    }
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++) {
            // St -> SK, capa = MAXN, cpf = dist[k][j][i]
            // SK -> St, capa = 0, cpf = -dist[k][j][i]
            addEdge(St + i, SK + j, MAXN, 0, dist[k][j][i]);
        }
    for (int i = 1; i <= N; i++) {
        // SK -> dest, capa = orders[i][k], cpf = 0
        // dest -> SK, capa = 0, cpf = 0
        addEdge(SK + i, dest, orders[i][k], 0, 0);
    }
}

bool check()
{
    for (int i = 0; i < edge[dest].size(); i++) {
        int u = edge[dest][i].v, j = edge[dest][i].p;
        if (edge[u][j].f < edge[u][j].c) return false;
    }

    return true;
}

bool work()
{
    if (init() == false) return false;

    int cost = 0;
    for (int k = 1; k <= K; k++) {
        buildEdge(k);

        int tmp = mcmf();
        if (check()) cost += tmp;
        else {
            puts("-1");
            return true;
        }
    }
    printf("%d\n", cost);

    return true;
}

int main()
{
    while (work()) ;

    return 0;
}

