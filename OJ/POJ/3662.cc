/*
 *  SRC: HDOJ 3662
 * PROB: Telephone Lines
 * ALGO: Dijkstra
 * DATE: Jul 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const int MAXP = 10010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, d;
    int k;
    Edge *next;

    bool operator <(const Edge &o) const
    {
        return d > o.d;
    }
};
Edge e_buf[MAXP << 1];
Edge *e_head[MAXN];
Edge *e_tail = e_buf;

priority_queue<Edge> que;
int dist[MAXN][MAXN];

inline void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, 0, e_head[u]};
    e_head[u] = e_tail++;
}

int main()
{
    int n, p, k;
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 0; i < p; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
        add_edge(v, u, d);
    }

    memset(dist, 0x3f, sizeof dist);
    que.push((Edge){1, 0, 0});
    while (!que.empty()) {
        Edge u = que.top();
        que.pop();
        if (u.d > dist[u.v][u.k]) continue;
        for (Edge *e = e_head[u.v]; e; e = e->next) {
            int v = e->v;
            int d = max(u.d, e->d);
            if (d < dist[v][u.k]) {
                dist[v][u.k] = d;
                que.push((Edge){v, d, u.k});
            }
            if (u.k + 1 <= k && u.d < dist[v][u.k + 1]) {
                dist[v][u.k + 1] = u.d;
                que.push((Edge){v, u.d, u.k + 1});
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, dist[n][i]);
    }
    printf("%d\n", ans == INF ? -1 : ans);

    return 0;
}

