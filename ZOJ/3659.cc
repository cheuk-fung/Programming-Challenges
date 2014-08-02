/*
 *  SRC: ZOJ 3659
 * PROB: Conquer a New Region
 * ALGO: Disjoint set
 * DATE: Oct 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

class Disjoint_set {
    public:
        int a[MAXN];

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
            int x = find(u);
            int y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

struct Edge {
    int u, v;
    long long d;
    bool operator<(const Edge &o) const { return d > o.d; }
} edge[MAXN];

long long f[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ds.build();
        for (int i = 1; i < n; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            edge[i - 1] = (Edge){u, v, d};
        }
        sort(edge, edge + n - 1);

        memset(f, 0, sizeof f);
        for (int i = 0; i < n - 1; i++) {
            int u = edge[i].u, v = edge[i].v;
            long long d = edge[i].d;
            int x = ds.find(u), y = ds.find(v);
            assert(x != y);
            long long a = f[x] + (-ds.a[y] * d), b = f[y] + (-ds.a[x] * d);
            if (a > b) {
                ds.join(x, y);
                f[x] = a;
            } else {
                ds.join(y, x);
                f[y] = b;
            }
        }

        printf("%lld\n", f[ds.find(1)]);
    }

    return 0;
}

