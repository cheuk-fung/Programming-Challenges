/*
 *  SRC: ZOJ 3653
 * PROB: Sleeper's Schedule
 * ALGO: DP
 * DATE: Sep 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int chkmax(int x, int y)
{
    if (x == INF) return y;
    return max(x, y);
}

struct Event {
    int s, e, v, l;

    bool operator<(const Event &o) const { return s < o.s; }
} e[1010];

int f[11010][122];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, t, K, l;
        scanf("%d%d%d%d", &n, &t, &K, &l);

        int chkmax_time = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &e[i].s, &e[i].e, &e[i].v);
            e[i].l = e[i].e - e[i].s;
            chkmax_time = chkmax(chkmax_time, e[i].e);
        }
        sort(e, e + n);

        int ans = 0;
        memset(f, 0x3f, sizeof f);
        f[0][0] = 0;
        for (int i = 0, j = 0; i <= chkmax_time; i++) {
            for (int k = 1; k <= t + l; k++) {
                if (i - 1 >= 0 && f[i - 1][k - 1] != INF) {
                    f[i][k] = chkmax(f[i][k], f[i - 1][k - 1]);
                }
                if (f[i][k] != INF) {
                    int dt = k - t;
                    if (dt >= 0) {
                        int val = f[i][k] - dt * dt;
                        int *p = &f[i + K + dt][0];
                        *p = chkmax(*p, val);

                        ans = max(ans, val);
                    } else {
                        ans = max(ans, f[i][k]);
                    }
                }
            }
            if (j < n) {
                while (e[j].s == i) {
                    for (int k = 0; k + e[j].l <= t + l; k++) {
                        if (f[i][k] == INF) continue;
                        int val = f[i][k] + e[j].v;
                        int *p = &f[i + e[j].l][k + e[j].l];
                        *p = chkmax(*p, val);
                    }
                    j++;
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

