/*
 *  SRC: POJ
 * TASK: Going Home
 * ALGO: MCMF
 * DATE: 06/10/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct Edge {
    int v, p;
    int c, f;
    int cpf;

    Edge(int vv, int pp, int cc, int ff, int cost)
        : v(vv), p(pp), c(cc), f(ff), cpf(cost)
    { }
};

const int MAXN = 210;
const int INF = 0x7f7f7f;
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

struct Point
{
    int x, y;

    Point(int xx, int yy)
        : x(xx), y(yy)
    { }
};

int N, M;
char map[MAXN][MAXN];
vector<Point> house, man;

bool work()
{
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return false;

    for (int i = 0; i < N; i++)
        scanf("%s", map[i]);

    house.clear();
    man.clear();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 'H') house.push_back(Point(i, j));
            else if (map[i][j] == 'm') man.push_back(Point(i, j));
        }

    /*
     * 0: src
     * 1 to N: house
     * N + 1 to N + N: man
     * MAXN: dest
     */

    for (int i = 0; i <= MAXN; i++) edge[i].clear();

    int hS = house.size(), mS = man.size();
    for (int i = 0; i < hS; i++) {
        edge[src].push_back(Edge(i + 1, edge[i + 1].size(), 1, 0, 0));
        edge[i + 1].push_back(Edge(src, edge[src].size() - 1, 0, 0, 0));
    }

    for (int i = 0; i < hS; i++)
        for (int j = 0; j < mS; j++) {
            int cost = abs(house[i].x - man[j].x) + abs(house[i].y - man[j].y);
            edge[i + 1].push_back(Edge(j + hS + 1, edge[j + hS + 1].size(), 1, 0, cost));
            edge[j + hS + 1].push_back(Edge(i + 1, edge[i + 1].size() - 1, 0, 0, -cost));
        }

    for (int i = 0; i < man.size(); i++) {
        edge[i + hS + 1].push_back(Edge(dest, edge[dest].size(), 1, 0, 0));
        edge[dest].push_back(Edge(i + hS + 1, edge[i + hS + 1].size() - 1, 0, 0, 0));
    }

    printf("%d\n", mcmf());

    return true;
}

int main()
{
    while (work()) ;

    return 0;
}
