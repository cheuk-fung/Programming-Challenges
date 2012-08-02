/*
 *  SRC: POJ 1087
 * PROB: A Plug for UNIX
 * ALGO: Dinic
 * DATE: Jul 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 300;
const int MAXE = 10000;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v, c, f;
    Edge *next, *rev;
} ebuf[MAXE];
Edge *ehead[MAXV], *ework[MAXE], *etail = ebuf;
int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, int c)
{
    *etail = (Edge){v, c, 0, ehead[u]};
    ehead[u] = etail++;
    *etail = (Edge){u, 0, 0, ehead[v]};
    ehead[v] = etail++;
    ehead[u]->rev = ehead[v];
    ehead[v]->rev = ehead[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof lev);
    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = ehead[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[dest] != -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *&e = ework[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) return res;
        }
    }
    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(ework, ehead, sizeof ehead);
        int f = dfs(orig, INF);
        if (!f) break;
        res += f;
    }
    return res;
}

map<string, int> type;
char name[30], name2[30];

int main()
{
    int n, idx = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        if (!type.count(name)) type[name] = idx++;
        add_edge(type[name], dest, 1);
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%*s%s", name);
        if (!type.count(name)) type[name] = idx++;
        add_edge(orig, type[name], 1);
    }

    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%s%s", name, name2);
        if (!type.count(name)) type[name] = idx++;
        if (!type.count(name2)) type[name2] = idx++;
        add_edge(type[name], type[name2], INF);
    }

    int r = dinic();
    printf("%d\n", m - r);

    return 0;
}

