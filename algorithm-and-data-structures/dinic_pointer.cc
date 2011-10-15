/*
 *  SRC: POJ 3281
 * PROB: Dining
 * ALGO: Dinic
 * DATE: Jun 2, 2011 
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
    Edge *next;
    Edge *rev; // revese edge
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
            int tmp = dfs(e->v, fmin(f - res, e->c - e->f));
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

void build_graph()
{
    int N, F, D;
    scanf("%d%d%d", &N, &F, &D);

    /*
     * 0: orig
     * 1 to F: FF
     * F + 1 to F + N: C1
     * F + N + 1 to F + 2N: C2
     * F + 2N + 1 to F + 2N + D: DD
     * MAX_N: dest
     */

    const int FF = 0;
    const int C1 = F, C2 = F + N;
    const int DD = F + 2 * N;

    for (int i = 1; i <= F; i++) {
        // orig -> FF, capa = 1
        // FF -> orig, capa = 0
        add_edge(orig, FF + i, 1);
    }
    for (int i = 1; i <= N; i++) {
        // C1 -> C2, capa = 1
        // C2 -> C1, capa = 0
        add_edge(C1 + i, C2 + i, 1);
    }
    for (int i = 1; i <=D; i++) {
        // DD -> dest, capa = 1
        // dest -> DD, capa = 0
        add_edge(DD + i, dest, 1);
    }

    for (int i = 1; i <= N; i++) {
        int f, d;
        scanf("%d%d", &f, &d);
        for (int j = 0; j < f; j++) {
            int tmp;
            scanf("%d", &tmp);
            // FF -> C1, capa = 1
            // C1 -> FF, capa = 0
            add_edge(FF + tmp, C1 + i, 1);
        }
        for (int j = 0; j < d; j++) {
            int tmp;
            scanf("%d", &tmp);
            // C2 -> DD, capa = 1
            // DD -> C2, capa = 0
            add_edge(C2 + i, DD + tmp, 1);
        }
    }
}

int main()
{
    memset(edge_buf, 0, sizeof(edge_buf));
    memset(edge_head, 0, sizeof(edge_head));
    edge_tail = edge_buf;

    build_graph();

    printf("%d\n", dinic());

    return 0;
}
