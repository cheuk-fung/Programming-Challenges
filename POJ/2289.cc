/*
 *  SRC: POJ 2289
 * PROB: Jamie's Contact Groups
 * ALGO: Dinic
 * DATE: Aug 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 2000;
const int MAXE = 4000000;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v, c, f;
    Edge *next, *rev;
};
Edge ebuf[MAXE];
Edge *ehead[MAXV], *ework[MAXV], *etail;
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
        int tmp = dfs(orig, INF);
        if (!tmp) break;
        res += tmp;
    }
    return res;
}

int n, m;
vector<int> grp[MAXV];
char line[10000];

bool check(int x)
{
    memset(ehead, 0, sizeof ehead);
    etail = ebuf;

    for (int i = 1; i <= n; i++) {
        add_edge(orig, i, 1);
        for (int j = 0 ; j < (int)grp[i].size(); j++) {
            add_edge(i, grp[i][j] + n + 1, 1);
        }
    }
    for (int i = 1; i <= m; i++) {
        add_edge(i + n, dest, x);
    }

    int r = dinic();
    return r == n;
}

int main()
{
    while (scanf("%d%d\n", &n, &m), n || m) {
        for (int i = 1; i <= n; i++) {
            grp[i].clear();
            gets(line);
            char *now = line;
            while (*now++ != ' ') ;

            int gid;
            while (~sscanf(now, "%d", &gid)) {
                grp[i].push_back(gid);
                if (gid == 0) now += 1;
                else now += (int)ceil(log10(gid + 1));
                while (*now == ' ') now++;
            }
        }

        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r - 1) >> 1;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }

        printf("%d\n", l);
    }

    return 0;
}

