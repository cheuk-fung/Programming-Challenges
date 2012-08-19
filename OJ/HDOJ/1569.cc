/*
 *  SRC: HDOJ 1569
 * PROB: 方格取数(2)
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

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 3000;
const int MAXE = 30000;

struct Arc {
    int v;
    long long c, f;
    Arc *next, *rev;
};
Arc arcbuf[MAXE << 1];
Arc *archead[MAXV], *arcwork[MAXV], *arctail;
int que[MAXV], lev[MAXV];

void addarc(int u, int v, long long c)
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

long long dfs(int u, long long f, int t)
{
    if (u == t) return f;

    long long res = 0;
    for (Arc *&p = arcwork[u]; p; p = p->next) {
        if (lev[p->v] == lev[u] + 1 && p->f < p->c) {
            long long r = dfs(p->v, min(f - res, p->c - p->f), t);
            res += r;
            p->f += r;
            p->rev->f = -p->f;
            if (res == f) break;
        }
    }
    return res;
}

long long dinic(int s, int t)
{
    long long res = 0;
    while (bfs(s, t)) {
        memcpy(arcwork, archead, sizeof archead);
        long long r = dfs(s, LLINF, t);
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
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int a;
                scanf("%d", &a);
                sum += a;

                int idx = i * m + j;
                if ((i & 1) == (j & 1)) {
                    addarc(s, idx, a);
                    if (i > 0)     addarc(idx, (i - 1) * m + j, LLINF);
                    if (i + 1 < n) addarc(idx, (i + 1) * m + j, LLINF);
                    if (j > 0)     addarc(idx, i * m + j - 1,   LLINF);
                    if (j + 1 < m) addarc(idx, i * m + j + 1,   LLINF);
                } else {
                    addarc(idx, t, a);
                }
            }
        }

        long long r = dinic(s, t);
        cout << sum - r << endl;
    }

    return 0;
}

