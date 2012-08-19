/*
 *  SRC: HDOJ 2883
 * PROB: kebab
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

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 1010;
const int MAXE = MAXV * MAXV;

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

struct Order {
    int s, e, v;
    bool operator<(const Order &o) const { return e < o.e; }
} orders[MAXV];
int tall[MAXV];

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;
        int s = MAXV - 1, t = s - 1;

        int tcnt = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            int si, ni, ei, ti;
            scanf("%d%d%d%d", &si, &ni, &ei, &ti);
            orders[i] = (Order){si, ei, ni * ti};
            tall[tcnt++] = si;
            tall[tcnt++] = ei;
            sum += ni * ti;
        }
        sort(tall, tall + tcnt);
        tcnt = unique(tall, tall + tcnt) - tall;
        for (int i = 1; i < tcnt; i++) {
            addarc(i + tcnt, t, m * (tall[i] - tall[i - 1]));
        }
        for (int i = 0; i < n; i++) {
            orders[i].s = lower_bound(tall, tall + tcnt, orders[i].s) - tall;
            orders[i].e = lower_bound(tall, tall + tcnt, orders[i].e) - tall;
        }

        sort(orders, orders + n);
        bool ok = true;
        for (int i = 0; i < n; i++) {
            addarc(s, orders[i].s, orders[i].v);
            for (int j = orders[i].s + 1; j <= orders[i].e; j++) {
                addarc(orders[i].s, j + tcnt, LLINF);
            }
            long long flow = dinic(s, t);
            if (flow != orders[i].v) {
                ok = false;
                break;
            }
        }

        puts(ok ? "Yes" : "No");
    }

    return 0;
}

