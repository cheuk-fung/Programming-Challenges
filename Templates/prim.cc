/*
 *  SRC: POJ 1258
 * PROB: Agri-Net
 * ALGO: Prim
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

const int MAXN = 110;

struct Edge
{
    int v, d;

    Edge(int _v, int _d)
        : v(_v), d(_d)
    { }

    bool operator<(const Edge& other) const
    {
        return d > other.d;
    }
};

int dist[MAXN];

bool prim()
{
    int n;
    if (scanf("%d", &n) == EOF) return false;

    vector<Edge> edge[MAXN];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int d;
            scanf("%d", &d);
            if (i != j) edge[i].push_back(Edge(j, d));
        }

    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;

    priority_queue<Edge> Q;
    Q.push(Edge(0, 0));

    int sum = 0;
    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (!dist[u] && u != 0) continue;
        sum += d;
        dist[u] = 0;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            int dis = edge[u][i].d;
            if (dis < dist[v]) {
                dist[v] = dis;
                Q.push(Edge(v, dist[v]));
            }
        }
    }

    printf("%d\n", sum);

    return true;
}

int main()
{
    while (prim()) ;

    return 0;
}

