/*
 *  SRC: HDOJ 4253
 * PROB: Two Famous Companies
 * ALGO: GOD LIKE
 * DATE: Jul 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

class Disjoint_Set {
    private:
        int a[MAXN];
    public:
        void reset() { memset(a, 0xff, sizeof a); }

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
};
Disjoint_Set ds;

struct Edge {
    int a, b, c, x;
};
Edge CT[MAXN], CU[MAXN], all[MAXN];

class Comparator {
    private:
        double eps;
    public:
        Comparator(double _eps) : eps(_eps) { }
        bool operator ()(const Edge &u, const Edge &v) const
        {
            double uc = u.c + (!u.x) * eps;
            double vc = v.c + (!v.x) * eps;
            return uc == vc ? u.x < v.x : uc < vc;
        }
};

int n, m, k;
int CT_cnt, CU_cnt;
double ans;

bool check(double eps)
{
    merge(CT, CT + CT_cnt, CU, CU + CU_cnt, all, Comparator(eps));

    ds.reset();
    int cnt = 0;
    ans = 0;
    for (int i = 0; i < m; i++) {
        if (ds.find(all[i].a) != ds.find(all[i].b)) {
            ds.join(all[i].a, all[i].b);
            ans += all[i].c;
            if (!all[i].x) {
                cnt++;
                ans += eps;
            }
        }
    }

    return cnt <= k;
}

int main()
{
    for (int task = 1; ~scanf("%d%d%d", &n, &m, &k); task++) {
        CT_cnt = CU_cnt = 0;
        for (int i = 0; i < m; i++) {
            int a, b, c, x;
            scanf("%d%d%d%d", &a, &b, &c, &x);
            if (!x) CT[CT_cnt++] = (Edge){a, b, c, x};
            else CU[CU_cnt++] = (Edge){a, b, c, x};
        }
        sort(CT, CT + CT_cnt, Comparator(0));
        sort(CU, CU + CU_cnt, Comparator(0));

        double l = -110, r = 110, mid;
        for (int time = 0; time < 20; time++) {
            mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }

        printf("Case %d: %d\n", task, (int)(ans - mid * k + 0.5));
    }

    return 0;
}

