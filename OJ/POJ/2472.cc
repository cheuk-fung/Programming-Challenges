/*
 *  SRC: POJ 2472
 * PROB: 106 miles to Chicago
 * ALGO: Dijkstra
 * DATE: Aug 24, 2011 
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

const int MAX_N = 110;

int n, m;

struct Edge {
    int v;
    double d;

    Edge(int _v, double _d)
        : v(_v), d(_d)
    { }

    bool operator < (const Edge& other) const
    {
        return d > other.d;
    }
};

vector<Edge> edge[MAX_N];

double dist[MAX_N];

double dijkstra()
{
    for (int i = 0; i < n; i++) dist[i] = 0.0;
    dist[0] = 1.0;

    priority_queue<Edge> Q;
    Q.push(Edge(0, 1.0));
    
    while (!Q.empty()) {
        int u = Q.top().v;
        double d = Q.top().d; 
        Q.pop();
        if (d < dist[u]) continue;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            double dis = edge[u][i].d;
            if (dis * dist[u] > dist[v]) {
                dist[v] = dis * dist[u];
                Q.push(Edge(v, dist[v]));
            }
        }
    }

    return dist[n - 1];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < m; i++) {
            int a, b, p;
            scanf("%d%d%d", &a, &b, &p);
            a--, b--;
            edge[a].push_back(Edge(b, p / 100.0));
            edge[b].push_back(Edge(a, p / 100.0));
        }
        printf("%.6f percent\n", dijkstra() * 100.0);

        for (int i = 0; i < n; i++) edge[i].clear();
    }

    return 0;
}
