/*
 *  SRC: HDOJ 4262
 * PROB: Juggler
 * ALGO: Disjoint set + BIT
 * DATE: Aug 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

inline int MIN(int a, int b) { return a < b ? a : b; }

class Disjoint_set {
    private:
        int a[MAXN];

    public:
        void build() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u), y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }

        int getsize(int u)
        {
            int x = find(u);
            return -a[x];
        }
} ds;

class BIT {
    public:
        int c[MAXN];

        void build() { memset(c, 0, sizeof c); }
        int lowbit(int x) { return x & -x; }

        void update(int x, int v)
        {
            for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ;
        }

        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

int hash[MAXN];
int vis[MAXN];

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        ds.build();
        bit.build();

        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            hash[a - 1] = i;
            vis[i] = 0;
            bit.update(i + 1, 1);
        }

        int now = 0;
        long long ans = 0;
        for (int i = 0, rest = n; i < n; i++, rest--) {
            int next = hash[i];
            vis[next] = 1;
            int cw, ccw;
            int a = bit.sum(now), b = bit.sum(next);
            if (now < next) {
                cw = b - a;
                ccw = a + rest - b;
            } else {
                cw = b + rest - a;
                ccw = a - b;
            }
            ans += MIN(cw, ccw) + 1;

            if (vis[(next + 1) % n]) {
                ds.join(next, (next + 1) % n);
            }
            now = (next + ds.getsize(next)) % n;
            bit.update(next + 1, -1);
        }

        printf("%I64d\n", ans);
    }

    return 0;
}

