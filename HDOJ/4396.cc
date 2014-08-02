/*
 *  SRC: HDOJ 4396
 * PROB: More lumber is required
 * ALGO: SSSP
 * DATE: Aug 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXV = 5010;
const int MAXE = 100010;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

struct Edge {
    int v;
    long long d;
    Edge *next;
} ebuf[MAXE << 1];
Edge *ehead[MAXV], *etail;

inline void addedge(int u, int v, long long d)
{
    *etail = (Edge){v, d, ehead[u]};
    ehead[u] = etail++;
}

struct Node {
    int u, k;
    long long d;

    bool operator<(const Node &o) const { return d == o.d ? k < o.k : d > o.d; }
};

long long dist[MAXV][510];

long long dijkstra(int s, int t, int k)
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<Node> que;
    que.push((Node){s, 0, 0ll});
    dist[s][0] = 0;
    while (!que.empty()) {
        Node top = que.top();
        que.pop();
        if (top.d > dist[top.u][top.k]) continue;
        for (Edge *e = ehead[top.u]; e; e = e->next) {
            long long td = top.d + e->d;
            int tk = top.k + 10;
            if (tk > k) tk = k;
            if (td < dist[e->v][tk]) {
                dist[e->v][tk] = td;
                que.push((Node){e->v, tk, td});
            }
        }
    }
    return dist[t][k] == LLINF ? -1 : dist[t][k];
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(ehead, 0, sizeof ehead);
        etail = ebuf;

        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            addedge(u, v, d);
            addedge(v, u, d);
        }

        int s, t, k;
        scanf("%d%d%d", &s, &t, &k);
        long long ret = dijkstra(s, t, k);
        cout << ret << endl;
    }

    return 0;
}

