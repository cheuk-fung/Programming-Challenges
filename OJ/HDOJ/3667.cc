/*
 *  SRC: HDOJ 3667
 * PROB: Transportation
 * ALGO: MCMF
 * DATE: Nov 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAX_N = 111;
const int MAX_EDGE_BUF_SIZE = 100000;
const int orig = 0, dest = 110;

struct Edge {
    int v;
    int c, f;
    int cpf;
    Edge *next;
    Edge *rev;
};
Edge edge_buf[MAX_EDGE_BUF_SIZE],
     *edge_tail,
     *edge_head[MAX_N];

struct Route {
    Route *next;
    Edge *which;
};
Route bfs_route[MAX_N];
int spfa_q[MAX_EDGE_BUF_SIZE], dist[MAX_N];
bool vis[MAX_N];

inline void add_edge(int u, int v, int c, int cpf)
{
    edge_tail->v = v;
    edge_tail->c = c;
    edge_tail->cpf = cpf;
    edge_tail->next = edge_head[u];
    edge_head[u] = edge_tail++;

    edge_tail->v = u;
    edge_tail->c = 0;
    edge_tail->cpf = -cpf;
    edge_tail->next = edge_head[v];
    edge_head[v] = edge_tail++;

    edge_head[u]->rev = edge_head[v];
    edge_head[v]->rev = edge_head[u];
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    int *q_head = spfa_q,
        *q_tail = spfa_q;
    *q_tail++ = orig;
    vis[orig] = true;
    dist[orig] = 0;
    bfs_route[orig].next = 0;

    while (q_head != q_tail) {
        int u = *q_head++;
        vis[u] = 0;
        Edge *e = edge_head[u];
        while (e) {
            if (e->cpf + dist[u] < dist[e->v] && e->f < e->c) {
                dist[e->v] = e->cpf + dist[u];
                bfs_route[e->v].next = &bfs_route[u];
                bfs_route[e->v].which = e;
                if (vis[e->v] == 0) {
                    vis[e->v] = 1;
                    *q_tail++ = e->v;
                }
            }
            e = e->next;
        }
    }

    return dist[dest] < INF;
}

int flow()
{
    int min_flow = INF;
    Route *r = &bfs_route[dest];
    while (r->next) {
        min_flow = min(min_flow, r->which->c - r->which->f);
        r = r->next;
    }

    int res = 0;
    r = &bfs_route[dest];
    while (r->next) {
        r->which->f += min_flow;
        res += r->which->cpf;
        r->which->rev->f = -r->which->f;
        r = r->next;
    }
    res *= min_flow;

    return res;
}

int mcmf()
{
    int res = 0;
    while (spfa()) res += flow();

    return res;
}

int mu[] = {1, 3, 5, 7, 9};

int main()
{
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        memset(edge_buf, 0, sizeof(edge_buf));
        memset(edge_head, 0, sizeof(edge_head));
        edge_tail = edge_buf;

        add_edge(orig, 1, k, 0);
        add_edge(n, dest, k, 0);
        for (int i = 0; i < m; i++) {
            int u, v, a, c;
            scanf("%d%d%d%d", &u, &v, &a, &c);
            for (int j = 0; j < c; j++)
                add_edge(u, v, 1, a * mu[j]);
        }

        int ans = mcmf();
        if (edge_head[dest]->rev->f == k) printf("%d\n", ans);
        else puts("-1");
    }

    return 0;
}
