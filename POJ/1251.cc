/*
 *  SRC: POJ 1251
 * PROB: Jungle Roads
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

const int MAX_N = 30;

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

int dist[MAX_N];

bool prim()
{
    int n;
    scanf("%d", &n);
    if (n == 0) return false;

    vector<Edge> edge[MAX_N];
    for (int i = 0; i < n - 1; i++) {
        char s[10];
        int k;
        scanf("%s%d", s, &k);
        for (int j = 0; j < k; j++) {
            int d;
            scanf("%s%d", s, &d);
            edge[i].push_back(Edge(s[0] - 'A', d));
            edge[s[0] - 'A'].push_back(Edge(i, d));
        }
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

