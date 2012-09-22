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
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAXV = 1010;
const int MAXE = 1000000;
const int orig = 0, dest = 1000;

struct Edge {
    int v;
    int c, f; // capa, flow
    int cpf; // cost per flow
    Edge *next,
         *rev; // revese edge
};
Edge e_buf[MAXE],
     *e_tail,
     *e_head[MAXV];

struct Rnode {
    Rnode *next;
    Edge *which; // which edge
};
Rnode road[MAXV];
int que[MAXE], dist[MAXV];
bool vis[MAXV];

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
    int f = INF;
    for (Rnode *r = &road[dest]; r->next; r = r->next)
        f = min(f, r->which->c - r->which->f);

    int res = 0;
    for (Rnode *r = &road[dest]; r->next; r = r->next) {
        r->which->f += f;
        res += r->which->cpf;
        r->which->rev->f = -r->which->f;
    }
    res *= f;

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
    memset(e_buf, 0, sizeof(e_buf));
    memset(e_head, 0, sizeof(e_head));
    e_tail = e_buf;

    build_graph();

    printf("%d\n", mcmf());

    return 0;
}
