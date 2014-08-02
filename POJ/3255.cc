/*
 *  SRC: POJ 3255
 * PROB: Roadblocks
 * ALGO: SSSP
 * DATE: Jul 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 5010;
const int MAXR = 100010;

struct Edge {
    int v, d;
    Edge *next;

    bool operator <(const Edge &o) const { return d > o.d; }
};
Edge e_buf[MAXR << 1];
Edge *e_head[MAXN];
Edge *e_tail = e_buf;

int dist[MAXN], revdist[MAXN];

inline void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

void dijkstra(int orig, int *dist)
{
    memset(dist, 0x3f, sizeof(int) * MAXN);
    dist[orig] = 0;
    priority_queue<Edge> que;
    que.push((Edge){orig, 0});
    while (!que.empty()) {
        Edge top = que.top();
        que.pop();
        if (top.d > dist[top.v]) continue;
        for (Edge *e = e_head[top.v]; e; e = e->next) {
            if (top.d + e->d < dist[e->v]) {
                dist[e->v] = top.d + e->d;
                que.push((Edge){e->v, dist[e->v]});
            }
        }
    }
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    for (int i = 0; i < r; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
        add_edge(v, u, d);
    }

    dijkstra(1, dist);
    dijkstra(n, revdist);

    int ans = INF;
    for (int u = 1; u <= n; u++) {
        for (Edge *e = e_head[u]; e; e = e->next) {
            int d = dist[u] + revdist[e->v] + e->d;
            if (d > dist[n] && d < ans) ans = d;
        }
    }

    printf("%d\n", ans);

    return 0;
}

