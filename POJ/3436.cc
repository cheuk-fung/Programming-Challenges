/*
 *  SRC: POJ
 * TASK: ACM Computer Factory
 * ALGO: Dinic
 * DATE: 06/10/2011 
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

const int INF = 0x7fffffff;
const int MAXN = 200;
const int src = 0, dest = MAXN;

vector<Edge> edge[MAXN + 1];
int dist[MAXN + 1];

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
        int tmp = dfs(src, MAXN);
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

struct Mac
{
    int val;
    int in[20], out[20];
} mac[100];

int P, N;
int start[20], end[20];

bool check(int* a, int* b)
{
    for (int i = 0; i < P; i++)
        if (a[i] + b[i] == 1) return false;
    return true;
}

int main()
{
    scanf("%d%d", &P, &N);

    for (int i = 0; i < P; i++) {
        start[i] = 0;
        end[i] = 1;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &mac[i].val);
        for (int j = 0; j < P; j++)
            scanf("%d", &mac[i].in[j]);
        for (int j = 0; j < P; j++)
            scanf("%d", &mac[i].out[j]);
    }

    for (int i = 0; i < N; i++)
        if (check(start, mac[i].in))
            addEdge(src, i + 1, INF, 0);

    for (int i = 0; i < N; i++)
        if (check(mac[i].out, end))
            addEdge(i + N + 1, dest, INF, 0);

    for (int i = 0; i < N; i++)
        addEdge(i + 1, i + N + 1, mac[i].val, 0);

    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j && check(mac[i].out, mac[j].in))
                    addEdge(i + N + 1, j + 1, INF, 0);

    printf("%d ", dinic());

    int cnt = 0;
    for (int i = N + 1; i < N * 2 + 1; i++)
        for (vector<Edge>::const_iterator e = edge[i].begin(); e != edge[i].end(); e++)
            if (e->v != dest && e->f > 0) cnt++;

    printf("%d\n", cnt);

    for (int i = N + 1; i < N * 2 + 1; i++)
        for (vector<Edge>::const_iterator e = edge[i].begin(); e != edge[i].end(); e++)
            if (e->v != dest && e->f > 0)
                printf("%d %d %d\n", i - N, e->v, e->f);
        

    return 0;
}
