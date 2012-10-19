/*
 *  SRC: POJ 2047
 * PROB: Concert Hall Scheduling
 * ALGO: DP
 * DATE: Oct 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Application {
    int l, r, v;

    bool operator<(const Application &o) const { return l < o.l; }
} app[1010];

class BIT {
    private:
        int c[500];
        int lowbit(int x) { return x & -x; }

    public:
        void update(int x, int v)
        {
            for ( ; x < 500; x += lowbit(x)) {
                c[x] = max(c[x], v);
            }
        }

        int query(int x)
        {
            int res = 0;
            for ( ; x > 0; x -= lowbit(x)) {
                res = max(res, c[x]);
            }
            return res;
        }
} bit[500];

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int m = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &app[i].l, &app[i].r, &app[i].v);
            m = max(m, app[i].r);
        }
        sort(app, app + n);

        memset(bit, 0, sizeof bit);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= 0; j--) {
                int now = bit[j].query(app[i].l) + app[i].v;
                bit[j].update(app[i].r + 1, now);
                bit[app[i].r].update(j + 1, now);
            }
        }
        for (int j = 0; j <= m; j++) {
            ans = max(ans, bit[j].query(m + 1));
        }

        printf("%d\n", ans);
    }

    return 0;
}

