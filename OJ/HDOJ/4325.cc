/*
 *  SRC: HDOJ 4325
 * PROB: Flowers
 * ALGO: Discrete
 * DATE: Aug 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1e5;

struct TPoint {
    int t, v, nt;

    bool operator <(const TPoint& o) const { return t < o.t; }
} pnt[MAXN << 1];

int cnt[MAXN << 1];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n << 1; i += 2) {
            scanf("%d", &pnt[i].t);
            pnt[i].v = 1;
            scanf("%d", &pnt[i + 1].t);
            pnt[i + 1].t++;
            pnt[i + 1].v = -1;
        }
        sort(pnt, pnt + 2 * n);

        memset(cnt, 0, sizeof cnt);
        pnt[0].nt = 0;
        cnt[0] = pnt[0].v;
        for (int i = 1; i < n << 1; i++) {
            if (pnt[i].t == pnt[i - 1].t) {
                pnt[i].nt = pnt[i - 1].nt;
                cnt[pnt[i].nt] += pnt[i].v;
            } else {
                pnt[i].nt = pnt[i - 1].nt + 1;
                cnt[pnt[i].nt] = cnt[pnt[i].nt - 1] + pnt[i].v;
            }
        }

        printf("Case #%d:\n", task);
        for (int i = 0; i < m; i++) {
            TPoint q;
            scanf("%d", &q.t);
            TPoint *r = upper_bound(pnt, pnt + 2 * n, q);
            if (r == pnt) {
                puts("0");
            } else {
                printf("%d\n", cnt[(r - 1)->nt]);
            }
        }
    }

    return 0;
}

