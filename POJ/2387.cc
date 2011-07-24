/*
 *  SRC: POJ 2387
 * PROB: Til the Cows Come Home
 * ALGO: Dijkstra
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

const int MAX_N = 1010;

struct Edge
{
    int v, d;

    Edge(int _v, int _d)
        : v(_v), d(_d)
    { }

    bool operator < (const Edge& other) const
    {
        return d > other.d;
    }
};

vector<Edge> edge[MAX_N + 1];

int shortest[MAX_N + 1];

int dijkstra(int n)
{
    memset(shortest, 0x3f, sizeof(shortest));
    shortest[0] = 0;

    priority_queue<Edge> Q;
    Q.push(Edge(0, 0));
    
    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (d > shortest[u]) continue;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            int dis = edge[u][i].d;
            if (dis + shortest[u] < shortest[v]) {
                shortest[v] = dis + shortest[u];
                Q.push(Edge(v, shortest[v]));
            }
        }
    }

    return shortest[n - 1];
}

int main()
{
    int t, n;
    scanf("%d%d", &t, &n);

    for (int i = 0; i < t; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        edge[u - 1].push_back(Edge(v - 1, d));
        edge[v - 1].push_back(Edge(u - 1, d));
    }

    printf("%d\n", dijkstra(n));

    return 0;
}
