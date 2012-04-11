/*
 *  SRC: HDOJ 3832
 * PROB: Earth Hour
 * ALGO: SPFA
 * DATE: Apr 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using std::queue;
using std::min;

const int INF = 0x3f3f3f3f;
const int MAX_V = 222;
const int MAX_E = 222 * 222 * 2;

int dist[3][MAX_V];
bool vis[MAX_V];

struct Edge {
    int v, d;
    Edge *next;
};
Edge e_buf[MAX_E],
     *e_head[MAX_V],
     *e_tail = e_buf;

void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

void spfa(int src, int *dist)
{
    memset(vis, false, sizeof(vis));
    dist[src] = 0;

    queue<int> Q;
    Q.push(src);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            int d = e->d;
            if (d + dist[u] < dist[v]) {
                dist[v] = d + dist[u];
                if (!vis[v]) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
}

struct Light {
    int x, y, r;
};
Light l[222];

inline int sqr(int a) { return a * a; }

inline bool intersect(const Light &a, const Light &b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y) <= sqr(a.r + b.r);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &l[i].x, &l[i].y, &l[i].r);
        }

        memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(l[i], l[j])) {
                    add_edge(i, j, 1);
                    add_edge(j, i, 1);
                }
            }
        }

        memset(dist, 0x3f, sizeof(dist));
        spfa(0, dist[0]);
        spfa(1, dist[1]);
        spfa(2, dist[2]);

        int ans = INF;
        for (int i = 0; i < n; i++) {
            if (dist[0][i] != INF && dist[1][i] != INF && dist[2][i] != INF) {
                ans = min(ans, dist[0][i] + dist[1][i] + dist[2][i]);
            }
        }

        printf("%d\n", ans == INF ? -1 : n - ans - 1);
    }

    return 0;
}

