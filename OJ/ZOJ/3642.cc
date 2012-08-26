/*
 *  SRC: ZOJ 3642
 * PROB: Just Another Information Sharing Problem
 * ALGO: Network flow
 * DATE: Aug 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

inline int MIN(int x, int y) { return x < y ? x : y; }

const int INF = 0x3f3f3f3f;
const int MAXV = 500;
const int MAXE = MAXV * MAXV;

struct Arc {
    int v, c, f;
    Arc *next, *rev;
};
Arc arcbuf[MAXE << 1];
Arc *archead[MAXV], *arcwork[MAXV], *arctail;

int que[MAXV], lev[MAXV];

inline void addarc(int u, int v, int c)
{
    *arctail = (Arc){v, c, 0, archead[u]};
    archead[u] = arctail++;
    *arctail = (Arc){u, 0, 0, archead[v]};
    archead[v] = arctail++;
    archead[u]->rev = archead[v];
    archead[v]->rev = archead[u];
}

bool bfs(int s, int t)
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = s;
    lev[s] = 0;

    while (head != tail) {
        int u = *head++;
        for (Arc *p = archead[u]; p; p = p->next) {
            if (lev[p->v] == -1 && p->f < p->c) {
                lev[p->v] = lev[u] + 1;
                *tail++ = p->v;
            }
        }
    }
    return lev[t] != -1;
}

int dfs(int u, int f, int t)
{
    if (u == t) return f;

    int res = 0;
    for (Arc *&p = arcwork[u]; p; p = p->next) {
        if (lev[p->v] == lev[u] + 1 && p->f < p->c) {
            int r = dfs(p->v, MIN(f - res, p->c - p->f), t);
            res += r;
            p->f += r;
            p->rev->f = -p->f;
            if (res == f) break;
        }
    }
    return res;
}

int dinic(int s, int t)
{
    int res = 0;
    while (bfs(s, t)) {
        memcpy(arcwork, archead, sizeof archead);
        int r = dfs(s, INF, t);
        if (!r) break;
        res += r;
    }
    return res;
}

map<int, int> info;

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        info.clear();
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;
        int s = MAXV - 1, t = s - 1;

        int idx = 0;
        for (int i = 0; i < n; i++) {
            int A, B, C;
            scanf("%d%d%d", &A, &B, &C);
            addarc(s, i, C);
            for (int j = 0; j < A; j++) {
                int x;
                scanf("%d", &x);
                if (!info.count(x)) info[x] = idx++;
                x = info[x];
                addarc(i, x + n, 1);
            }
        }
        for (int i = 0; i < idx; i++) {
            addarc(i + n, t, 1);
        }

        int m;
        scanf("%d", &m);
        addarc(s, m - 1, INF);

        int r = dinic(s, t);
        printf("%d\n", r);
    }

    return 0;
}

