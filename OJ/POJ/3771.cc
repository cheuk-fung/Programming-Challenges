/*
 *  SRC: POJ 3771
 * PROB: World Islands
 * ALGO: MST
 * DATE: Sep 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 55;

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
            int x = find(u);
            int y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

struct Point {
    int x, y;
} pnt[MAXN];

struct Edge {
    int u, v;
    double d;

    bool operator<(const Edge &o) const { return d < o.d; }
} e[MAXN * MAXN];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].x, &pnt[i].y);
        }

        int ecnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = sqrt((pnt[i].x - pnt[j].x) * (pnt[i].x - pnt[j].x) + (pnt[i].y - pnt[j].y) * (pnt[i].y - pnt[j].y));
                e[ecnt++] = (Edge){i, j, dist};
            }
        }
        sort(e, e + ecnt);

        double ans = 1e10;
        for (int i = 0; i < n; i++) {
            ds.build();
            double mst = 0;
            for (int j = 0; j < ecnt; j++) {
                if (e[j].u == i || e[j].v == i) continue;
                if (ds.find(e[j].u) != ds.find(e[j].v)) {
                    ds.join(e[j].u, e[j].v);
                    mst += e[j].d;
                }
            }
            ans = min(ans, mst);
        }

        printf("%.2f\n", ans);
    }

    return 0;
}

