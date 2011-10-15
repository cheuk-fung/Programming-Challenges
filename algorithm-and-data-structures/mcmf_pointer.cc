/*
 *  SRC: POJ 2135
 * PROB: Farm Tour
 * ALGO: MCMF
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

inline int fmin(int a, int b) { return a < b ? a : b; }

const int INF = 0x3f3f3f3f;
const int MAX_N = 1010;
const int MAX_EDGE_BUF_SIZE = 1000000;
const int orig = 0, dest = 1000;

struct Edge {
    int v;
    int c, f; // capa, flow
    int cpf; // cost per flow
    Edge *next;
    Edge *rev; // revese edge
};
Edge edge_buf[MAX_EDGE_BUF_SIZE],
     *edge_tail,
     *edge_head[MAX_N];

struct Route {
    Route *next;
    Edge *which; // which edge
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
        vis[u] = false;
        Edge *e = edge_head[u];
        while (e) {
            if (e->cpf + dist[u] < dist[e->v] && e->f < e->c) {
                dist[e->v] = e->cpf + dist[u];
                bfs_route[e->v].next = &bfs_route[u];
                bfs_route[e->v].which = e;
                if (vis[e->v] == false) {
                    vis[e->v] = true;
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
        min_flow = fmin(min_flow, r->which->c - r->which->f);
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

void build_graph()
{
    int n, m;
    scanf("%d%d", &n, &m);
    add_edge(orig, 1, 2, 0);
    for (int i = 0; i < m; i++) {
        int s, e, v;
        scanf("%d%d%d", &s, &e, &v);
        add_edge(s, e, 1, v);
        add_edge(e, s, 1, v);
    }
    add_edge(n, dest, 2, 0);
}

int main()
{
    memset(edge_buf, 0, sizeof(edge_buf));
    memset(edge_head, 0, sizeof(edge_head));
    edge_tail = edge_buf;

    build_graph();

    printf("%d\n", mcmf());

    return 0;
}
