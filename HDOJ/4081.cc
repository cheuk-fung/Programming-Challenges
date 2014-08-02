/*
 *  SRC: HDOJ 4081
 * PROB: Qin Shi Huang's National Road System
 * ALGO: MST + Tree DP
 * DATE: Sep 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Disjoint_set {
    private:
        int a[1010];

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

struct Edge {
    int u, v;
    double d;

    bool operator<(const Edge &o) const { return d < o.d; }
} e[1010 * 1010];

struct Arc {
    int v;
    double d;
};
vector<Arc> arc[1010];

struct Point {
    int x, y, p;
} pnt[1010];

inline int SQR(int x) { return  x * x; }
inline double dist(int a, int b) { return sqrt((double)(SQR(pnt[a].x - pnt[b].x) + SQR(pnt[a].y - pnt[b].y))); }

double f[1010];

void dfs(int u, int parent, double now)
{
    for (int i = 0; i < (int)arc[u].size(); i++) {
        int v = arc[u][i].v;
        if (v != parent) {
            f[v] = max(arc[u][i].d, now);
            dfs(v, u, f[v]);
        }
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &pnt[i].x, &pnt[i].y, &pnt[i].p);
            arc[i].clear();
        }

        int ecnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                e[ecnt++] = (Edge){i, j, dist(i, j)};
            }
        }
        sort(e, e + ecnt);

        ds.build();
        double mst = 0;
        for (int i = 0; i < ecnt; i++) {
            if (ds.find(e[i].u) != ds.find(e[i].v)) {
                ds.join(e[i].u, e[i].v);
                mst += e[i].d;
                arc[e[i].u].push_back((Arc){e[i].v, dist(e[i].u, e[i].v)});
                arc[e[i].v].push_back((Arc){e[i].u, dist(e[i].u, e[i].v)});
            }
        }

        double ans = 0;
        for (int i = 0; i < n; i++) {
            memset(f, 0, sizeof f);
            dfs(i, -1, 0);
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                int A = pnt[i].p + pnt[j].p;
                double B = mst - f[j];
                ans = max(ans, A / B);
            }
        }

        printf("%.2f\n", ans);
    }

    return 0;
}

