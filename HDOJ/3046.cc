/*
 *  SRC: HDOJ 3046
 * PROB: Pleasant sheep and big big wolf
 * ALGO: Network flow
 * DATE: Aug 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 200 * 200 + 10;
const int MAXE = 200 * 200 * 10;

struct Arc {
    int v, c, f;
    Arc *next, *rev;
} arcbuf[MAXE << 1];
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
            int r = dfs(p->v, min(f - res, p->c - p->f), t);
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

int mat[200][200];

int main()
{
    int task = 1;
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;
        int s = MAXV - 1, t = s - 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int idx = i * m + j;
                int a;
                scanf("%d", &a);
                if (a == 1) addarc(s, idx, INF);
                else if (a == 2) addarc(idx, t, INF);

                if (i > 0)     addarc(idx, (i - 1) * m + j, 1);
                if (i + 1 < n) addarc(idx, (i + 1) * m + j, 1);
                if (j > 0)     addarc(idx, i * m + j - 1,   1);
                if (j + 1 < m) addarc(idx, i * m + j + 1,   1);
            }
        }

        int r = dinic(s, t);
        printf("Case %d:\n%d\n", task++, r);
    }

    return 0;
}

