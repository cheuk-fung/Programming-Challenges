/*
 *  SRC: HDOJ 2485
 * PROB: Destroying the bus stations
 * ALGO: Dinic
 * DATE: Nov 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAX_N = 110;
const int MAX_EDGE_BUF_SIZE = 10010;
int orig = 2, dest;

struct Edge {
    int v;
    int c, f;
    Edge *next;
    Edge *rev;
};
Edge edge_buf[MAX_EDGE_BUF_SIZE],
     *edge_tail,
     *edge_head[MAX_N];

int bfs_q[MAX_N], lev[MAX_N];

inline void add_edge(int u, int v, int c)
{
    edge_tail->v = v;
    edge_tail->c = c;
    edge_tail->next = edge_head[u];
    edge_head[u] = edge_tail++;

    edge_tail->v = u;
    edge_tail->c = 0;
    edge_tail->next = edge_head[v];
    edge_head[v] = edge_tail++;

    edge_head[u]->rev = edge_head[v];
    edge_head[v]->rev = edge_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

    int *q_head = bfs_q,
        *q_tail = bfs_q;
    *q_tail++ = orig;
    lev[orig] = 0;

    while (q_head != q_tail) {
        int u = *q_head++;
        Edge *e = edge_head[u];
        while (e) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *q_tail++ = e->v;
            }
            e = e->next;
        }
    }

    return lev[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    Edge *e = edge_head[u];
    while (e) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }
        e = e->next;
    }

    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        int tmp = dfs(orig, MAX_N);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}
int map[MAX_N][MAX_N], dist[MAX_N][MAX_N];

int n, m, K;

int main()
{
    while (scanf("%d%d%d", &n, &m, &K), n && m && K) {
        memset(map, 0, sizeof(map));
        memset(dist, 0x3f, sizeof(dist));
        memset(edge_buf, 0, sizeof(edge_buf));
        memset(edge_head, 0, sizeof(edge_head));
        edge_tail = edge_buf;
        dest = n * 2 - 1;

        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            dist[x][y] = map[x][y] = 1;
        }

        for (int i = 1; i <= n; i++) dist[i][i] = 0;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

        for (int i = 2; i < n; i++)
            add_edge(i * 2 - 1, i * 2, 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (map[i][j]) {
                    if (dist[1][i] + dist[j][n] + 1 <= K)
                        add_edge(i * 2, j * 2 - 1, 1);
                }

        printf("%d\n", dinic());
    }

    return 0;
}
