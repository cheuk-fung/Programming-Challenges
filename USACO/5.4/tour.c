/*
ID: os.idea1
LANG: C
TASK: tour
*/
#include <stdio.h>
#include <string.h>

#define CHARSET_SIZE 256
#define NODE_MAX_SIZE 10000
#define INF 0x3f3f3f3f

FILE *fin, *fout;

inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int orig, dest;

struct Tnode {
    struct Tnode *next[CHARSET_SIZE];
    int id;
};
struct Tnode node[NODE_MAX_SIZE],
             *node_tail,
             *trie;

int trie_insert(char *s, int id)
{
    struct Tnode *p = trie;
    while (*s) {
        int idx = *s++;
        if (!p->next[idx]) p->next[idx] = node_tail++;
        p = p->next[idx];
    }
    if (!p->id) p->id = id;

    return p->id;
}

struct Edge {
    int v;
    int c, f;
    int cpf;
    struct Edge *next, *rev;
};
struct Edge edge_buf[30000],
            *edge_tail,
            *edge_head[1000];

struct Route {
    int u, v;
    struct Edge *rev;
};
struct Route bfs_route[1000];

int bfs_q[10000], vis[1000], dist[1000];

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

int spfa()
{
    memset(vis, 0, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    int *q_head = bfs_q, *q_tail = bfs_q;
    *q_tail++ = orig;
    vis[orig] = 1;
    dist[orig] = 0;
    bfs_route[orig] = (struct Route){-1, orig, 0};

    while (q_head != q_tail) {
        int u = *q_head++;
        vis[u] = 0;
        struct Edge *e = edge_head[u];
        while (e) {
            int v = e->v,
                cpf = e->cpf;
            if (cpf + dist[u] < dist[v] && e->f < e->c) {
                dist[v] = cpf + dist[u];
                bfs_route[v] = (struct Route){u, v, e};
                if (!vis[v]) {
                    vis[v] = 1;
                    *q_tail++ = v;
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
    struct Route *r = &bfs_route[dest];
    while (r->u != -1) {
        min_flow = min(min_flow, r->rev->c - r->rev->f);
        r = &bfs_route[r->u];
    }

    int res = 0;
    r = &bfs_route[dest];
    while (r->u != -1) {
        r->rev->f += min_flow;
        res += r->rev->cpf;
        r->rev->rev->f = -r->rev->f;
        r = &bfs_route[r->u];
    }
    res *= min_flow;

    return res;
}

int mcmf()
{
    int res = 0;
    while (spfa()) res -= flow();
    return res;
}

int n, m;
char city[20];

int main()
{
    fin = fopen("tour.in", "r");
    fout = fopen("tour.out", "w");

    node_tail = node;
    trie = node_tail++;
    
    edge_tail = edge_buf;

    fscanf(fin, "%d%d", &n, &m);
    orig = 1;
    dest = n * 2;

    int i;
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%s", city);
        trie_insert(city, i);
    }

    add_edge(1, 2, 2, 0);
    for (i = 2; i < n; i++)
        add_edge(i * 2 - 1, i * 2, 1, -1);

    for (i = 1; i <= m; i++) {
        int a, b;
        fscanf(fin, "%s", city);
        a = trie_insert(city, 0);
        fscanf(fin, "%s", city);
        b = trie_insert(city, 0);
        if (a > b) swap(&a, &b);
        add_edge(a * 2, b * 2 - 1, 1, 0);
    }
    add_edge(n * 2 - 1, n * 2, 2, 0);

    int ans = mcmf() + 2;
    fprintf(fout, "%d\n", (edge_tail - 2)->f == 2 ? ans : 1);

    return 0;
}
