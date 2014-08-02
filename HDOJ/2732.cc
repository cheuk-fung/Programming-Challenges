/*
 *  SRC: HDOJ 2732
 * PROB: Leapin' Lizards
 * ALGO: Network flow
 * DATE: Aug 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 1000;
const int MAXE = 100000;

struct Arc {
    int v;
    int c, f;
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

char jumps[30][30], lizards[30][30];
inline int VIN(int x) { return x << 1; }
inline int VOUT(int x) { return x << 1 | 1; }
inline int SQR(int x) { return x * x; }
inline int dist(int x1, int y1, int x2, int y2) { return SQR(x1 - x2) + SQR(y1 - y2); }

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;
        int s = MAXV - 1, t = s - 1;

        int n, d;
        scanf("%d%d", &n, &d);
        d *= d;
        for (int i = 0; i < n; i++) {
            scanf("%s", jumps[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%s", lizards[i]);
        }

        int lizardcnt = 0;
        int m = strlen(jumps[0]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (jumps[i][j] == '0') continue;
                int idx = i * m + j;
                addarc(VIN(idx), VOUT(idx), jumps[i][j] - '0');

                if (lizards[i][j] == 'L') {
                    addarc(s, VIN(idx), 1);
                    lizardcnt++;
                }

                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < m; l++) {
                        if (k == i && l == j) continue;
                        if (jumps[i][j] == '0') continue;
                        if (dist(i, j, k, l) <= d) addarc(VOUT(idx), VIN(k * m + l), INF);
                    }
                }

                bool ok = false;
                for (int k = -1; k <= m; k++) {
                    if (dist(i, j, -1, k) <= d || dist(i, j, n, k) <= d) {
                        addarc(VOUT(idx), t, INF);
                        ok = true;
                        break;
                    }
                }
                if (ok) continue;
                for (int k = -1; k <= n; k++) {
                    if (dist(i, j, k, -1) <= d || dist(i, j, k, m) <= d) {
                        addarc(VOUT(idx), t, INF);
                        break;
                    }
                }
            }
        }

        int r = dinic(s, t);
        printf("Case #%d: ", task);
        if (r == lizardcnt) {
            puts("no lizard was left behind.");
        } else {
            printf("%d lizard%s left behind.\n", lizardcnt - r, lizardcnt - r == 1 ? " was" : "s were");
        }
    }

    return 0;
}

