/*
 *  SRC: HDOJ 3873
 * PROB: Invade the Mars
 * ALGO: Dijkstra
 * DATE: May 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV = 3010;
const int MAXE = 70010;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

long long dist[MAXV];
long long arr_time[MAXV];
int degree[MAXV];
bool vis[MAXV];

struct Edge {
    int v;
    long long d;
    Edge *next;

    bool operator<(const Edge &o) const
    {
        return d > o.d;
    }
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_tail;

Edge p_buf[MAXE];
Edge *p_head[MAXV];
Edge *p_tail;

inline void add_edge(int u, int v, long long d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

inline void add_pedge(int u, int v)
{
    *p_tail = (Edge){v, 0, p_head[u]};
    p_head[u] = p_tail++;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;

    priority_queue<Edge> que;
    que.push((Edge){1, 0, 0});
    while (!que.empty()) {
        int u = que.top().v;
        long long td = que.top().d;
        que.pop();
        if (td > dist[u]) continue;

        for (Edge *e = p_head[u]; e; e = e->next) {
            int v = e->v;
            arr_time[v] = max(arr_time[v], td);
            degree[v]--;
            if (!degree[v]) {
                dist[v] = max(dist[v], arr_time[v]);
                que.push((Edge){v, dist[v], 0});
            }
        }

        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            int d = e->d;
            if (d + dist[u] < dist[v]) {
                dist[v] = max(d + dist[u], arr_time[v]);
                if (!degree[v]) {
                    que.push((Edge){v, dist[v], 0});
                }
            }
        }
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;
        memset(p_head, 0, sizeof(p_head));
        p_tail = p_buf;
        memset(arr_time, 0, sizeof(arr_time));

        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            add_edge(u, v, d);
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d", &degree[i]);
            for (int j = 0; j < degree[i]; j++) {
                int p;
                scanf("%d", &p);
                add_pedge(p, i);
            }
        }

        dijkstra();

        printf("%lld\n", dist[n]);
    }

    return 0;
}
