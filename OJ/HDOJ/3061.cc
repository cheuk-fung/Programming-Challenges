/*
 *  SRC: HDOJ 3061
 * PROB: Battle
 * ALGO: Network flow
 * DATE: Aug 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 555;
const int MAXE = MAXV * MAXV;

struct Arc {
    int v, c, f;
    Arc *next, *rev;
};
Arc arcbuf[MAXE << 1];
Arc *archead[MAXV], *arcwork[MAXV], *arctail;
int que[MAXV], lev[MAXV];

void addarc(int u, int v, int c)
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

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;
        int s = MAXV - 1, t = s - 1;

        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int v;
            scanf("%d", &v);
            if (v > 0) {
                addarc(s, i, v);
                sum += v;
            } else if (v < 0) {
                addarc(i, t, -v);
            }
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addarc(a, b, INF);
        }

        int r = dinic(s, t);
        printf("%d\n", sum - r);
    }

    return 0;
}

