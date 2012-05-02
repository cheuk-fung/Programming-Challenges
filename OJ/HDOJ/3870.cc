/*
 *  SRC: HDOJ 3870
 * PROB: Catch the Theves
 * ALGO: Dijkstra
 * DATE: Apr 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV = 500 * 500;
const int MAXE = MAXV * 10;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
const int orig = 0, dest = MAXV - 1;

long long dist[MAXV];
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

inline void add_edge(int u, int v, long long d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[orig] = 0;

    priority_queue<Edge> que;
    que.push((Edge){orig, 0, 0});
    while (!que.empty()) {
        int u = que.top().v;
        long long d = que.top().d;
        que.pop();
        if (d > dist[u]) continue;
        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            int dis = e->d;
            int new_dist = dis + dist[u];
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                que.push((Edge){v, dist[v], 0});
            }
        }
    }
}

int A[500][500];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        int m = n - 1;
        for (int j = 0; j < m; j++) {
            add_edge(orig, j + 1, A[0][j]);
            add_edge((m - 1) * m + j + 1, dest, A[n - 1][j]);
        }
        for (int i = 0; i < m; i++) {
            add_edge(orig, i * m + m, A[i][n - 1]);
            add_edge(i * m + 1, dest, A[i][0]);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                int id = i * m + j + 1;
                if (j + 1 < m) {
                    add_edge(id, id + 1, A[i][j + 1]);
                    add_edge(id + 1, id, A[i][j + 1]);
                }
                if (i + 1 < m) {
                    add_edge(id, id + m, A[i + 1][j]);
                    add_edge(id + m, id, A[i + 1][j]);
                }
            }
        }

        dijkstra();

        printf("%I64d\n", dist[dest]);
    }

    return 0;
}
