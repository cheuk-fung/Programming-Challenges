/*
 *  SRC: HDOJ 2448
 * PROB: Mining Station on the Sea
 * ALGO: MCMF
 * DATE: Feb 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAX_V = 510;
const int MAX_E = 510000;
const int orig = 0, dest = 500;

struct Edge {
    int v;
    int c, f;
    int cpf;
    Edge *next,
         *rev;
};
Edge e_buf[MAX_E],
     *e_tail,
     *e_head[MAX_V];

struct RoadNode {
    RoadNode *next;
    Edge *which;
};
RoadNode road[MAX_V];
int que[MAX_E], dist[MAX_V];
bool vis[MAX_V];

inline void add_edge(int u, int v, int c, int cpf)
{
    *e_tail = (Edge){v, c, 0, cpf, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, -cpf, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    int *head = que,
        *tail = que;
    *tail++ = orig;
    vis[orig] = true;
    dist[orig] = 0;
    road[orig].next = 0;

    while (head != tail) {
        int u = *head++;
        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next)
            if (e->cpf + dist[u] < dist[e->v] && e->f < e->c) {
                dist[e->v] = e->cpf + dist[u];
                road[e->v].next = &road[u];
                road[e->v].which = e;
                if (vis[e->v] == false) {
                    vis[e->v] = true;
                    *tail++ = e->v;
                }
            }
    }

    return dist[dest] < INF;
}

int flow()
{
    int min_flow = INF;
    for (RoadNode *r = &road[dest]; r->next; r = r->next)
        min_flow = min(min_flow, r->which->c - r->which->f);

    int res = 0;
    for (RoadNode *r = &road[dest]; r->next; r = r->next) {
        r->which->f += min_flow;
        res += r->which->cpf;
        r->which->rev->f = -r->which->f;
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

int station[500];

int main()
{
    int n, m, k, p;
    while (~scanf("%d%d%d%d", &n, &m, &k, &p)) {
        memset(station, 0, sizeof(station));
        memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            station[t]++;
        }
        for (int i = 1; i <= m; i++)
            if (station[i]) add_edge(orig, i, station[i], 0);
        for (int i = 0; i < k; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, INF, c);
            add_edge(b, a, INF, c);
        }
        for (int i = 0; i < p; i++) {
            int d, e, f;
            scanf("%d%d%d", &d, &e, &f);
            add_edge(e, m + d, INF, f);
        }
        for (int i = 1; i <= n; i++)
            add_edge(m + i, dest, 1, 0);

        printf("%d\n", mcmf());
    }

    return 0;
}
