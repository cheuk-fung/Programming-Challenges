#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

const int MAXN = ;

struct Edge {
    int v, d;

    Edge(int _v, int _d)
        : v(_v), d(_d)
    { }

    bool operator<(const Edge& other) const
    {
        return d > other.d;
    }
};

vector<Edge> edge[MAXN];

int dist[MAXN];

int dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;

    priority_queue<Edge> Q;
    Q.push(Edge(0, 0));

    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (d > dist[u]) continue;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            int dis = edge[u][i].d;
            if (dis + dist[u] < dist[v]) {
                dist[v] = dis + dist[u];
                Q.push(Edge(v, dist[v]));
            }
        }
    }

    return something;
}
