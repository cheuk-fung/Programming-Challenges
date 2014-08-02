/*
 *  SRC: HDOJ 4304
 * PROB: Hourai Jeweled
 * ALGO: DP
 * DATE: Jul 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<long long, long long> pii;
const int MAXN = 300010;

struct Edge {
    int v, c;
    Edge *next;
};
Edge e_buf[MAXN << 1];
Edge *e_head[MAXN];
Edge *e_tail;

struct OEdge {
    int u, v, c;

    bool operator <(const OEdge &o) const
    {
        return c < o.c;
    }
};
OEdge oe[MAXN];

int vexval[MAXN];
long long ans;

inline void add_edge(int u, int v, int c)
{
    *e_tail = (Edge){v, c, e_head[u]};
    e_head[u] = e_tail++;
}

pii dp(int u, int parent, int pcolor)
{
    pii r(0, 0);
    long long totval = 0, totcnt = 0;
    long long val = 0, cnt = 0;
    int pc = 0;

    for (Edge *e = e_head[u]; e; e = e->next) {
        if (e->v != parent) {
            pii rc = dp(e->v, u, e->c);
            ans += rc.first + rc.second * vexval[u];
            if (e->c != pcolor) {
                r.first += rc.first + rc.second * vexval[u];
                r.second += rc.second;
            }
            if (e->c != pc) {
                ans += totval * cnt + totcnt * val + totcnt * cnt * vexval[u];
                totval += val;
                totcnt += cnt;
                val = cnt = 0;
                pc = e->c;
            }
            val += rc.first;
            cnt += rc.second;
        }
    }
    ans += totval * cnt + totcnt * val + totcnt * cnt * vexval[u];

    return pii(r.first + vexval[u], r.second + 1);
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 1; i <= n; i++) scanf("%d", vexval + i);
        for (int i = 0; i < n - 1; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            oe[i] = (OEdge){u, v, c};
        }
        sort(oe, oe + n - 1);
        for (int i = 0; i < n - 1; i++) {
            add_edge(oe[i].u, oe[i].v, oe[i].c);
            add_edge(oe[i].v, oe[i].u, oe[i].c);
        }

        ans = 0;
        dp(1, 0, 0);
        cout << ans << endl;
    }

    return 0;
}

