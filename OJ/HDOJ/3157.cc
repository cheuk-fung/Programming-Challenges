/*
 *  SRC: HDOJ 3157
 * PROB: Crazy Circuits
 * ALGO: Network flow
 * DATE: Aug 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 55;
const int MAXE = 55 * 55 * 4;

struct Arc {
    int v, c ,f;
    bool clear;
    Arc *next, *rev;
};
Arc arcbuf[MAXE];
Arc *archead[MAXV], *arcwork[MAXV], *arctail;
int que[MAXV], lev[MAXV];

inline void addarc(int u, int v, int c, bool clear = false)
{
    *arctail = (Arc){v, c, 0, clear, archead[u]};
    archead[u] = arctail++;
    *arctail = (Arc){u, 0, 0, clear, archead[v]};
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
    while (scanf("%d%d", &n, &m), n || m) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;

        int s = MAXV - 1, t = s - 1;
        int vs = t - 1, vt = vs - 1;
        int vsum = 0;
        for (int i = 0; i < m; i++) {
            int pi, ni, Ii;
            char buf[10];
            scanf(" %s", buf);
            if (buf[0] == '+') pi = s;
            else sscanf(buf, "%d", &pi);
            scanf(" %s", buf);
            if (buf[0] == '-') ni = t;
            else sscanf(buf, "%d", &ni);
            scanf("%d", &Ii);
            addarc(pi, ni, INF);
            addarc(pi, vt, Ii, true);
            addarc(vs, ni, Ii, true);
            vsum += Ii;
        }
        addarc(t, s, INF, true);

        int r = dinic(vs, vt);
        if (r != vsum) {
            puts("impossible");
        } else {
            for (Arc *p = arcbuf; p != arctail; p++) {
                if (p->clear) p->f = p->c;
            }
            dinic(t, s);
            int ans = 0;
            for (Arc *p = archead[s]; p; p = p->next) {
                ans += p->f;
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}

