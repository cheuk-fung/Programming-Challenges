/*
 *  SRC: HDOJ 4307
 * PROB: Matrix
 * ALGO: Dinic
 * DATE: Jul 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 1010;
const int MAXE = MAXV * MAXV;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    long long c, f;
    Edge *next;
    Edge *rev;
};
Edge e_buf[MAXE << 1];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, long long c)
{
    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;

    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }

    return lev[dest] != -1;
}

long long dfs(int u, long long f)
{
    if (u == dest) return f;

    long long res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            long long tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }
    }

    return res;
}

long long dinic()
{
    long long res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof e_head);
        long long tmp = dfs(orig, INF);
        if (tmp) res += tmp;
        else break;
    }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(e_head, 0, sizeof e_head);
        e_tail = e_buf;

        int n;
        scanf("%d", &n);

        long long sum = 0;
        for (int i = 0; i < n; i++) {
            long long row = 0;
            for (int j = 0; j < n; j++) {
                int B;
                scanf("%d", &B);
                row += B;
                sum += B;
                add_edge(i + 1, j + 1, B);
            }
            add_edge(orig, i + 1, row);
        }
        for (int i = 0; i < n; i++) {
            int C;
            scanf("%d", &C);
            add_edge(i + 1, dest, C);
        }

        cout << sum - dinic() << endl;
    }

    return 0;
}

