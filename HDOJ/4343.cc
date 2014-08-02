/*
 *  SRC: HDOJ 4343
 * PROB: Interval query
 * ALGO: Doubling
 * DATE: Aug 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 100010;

struct Interval {
    int l, r;
    int nl, nr;
    int type;

    bool operator<(const Interval &o) const { return l == o.l ? r > o.r : l < o.l; }
};
vector<int> endpoints(MAXN << 2);
vector<Interval> inv(MAXN);
vector<Interval> ninv(MAXN);
vector<Interval> query(MAXN);
map<int, int> discrete;

int f[21][MAXN << 2];

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        endpoints.clear();
        inv.clear();
        ninv.clear();
        query.clear();
        discrete.clear();
        memset(f, 0x3f, sizeof f);
        // printf("%d\n", sizeof f / 1024);

        for (int i = 0; i < n; i++) {
            Interval t;
            t.type = 0;
            scanf("%d%d", &t.l, &t.r);
            inv.push_back(t);
            endpoints.push_back(t.l);
            endpoints.push_back(t.r);
        }
        sort(inv.begin(), inv.end());

        for (int i = 0; i < m; i++) {
            Interval t;
            t.type = 1;
            scanf("%d%d", &t.l, &t.r);
            query.push_back(t);
            endpoints.push_back(t.l);
            endpoints.push_back(t.r);
        }
        sort(endpoints.begin(), endpoints.end());

        int idx = 0;
        for (int i = 0; i < (int)endpoints.size(); i++) {
            if (discrete.count(endpoints[i]) == 0) discrete[endpoints[i]] = idx++;
        }
        for (int i = 0; i < (int)inv.size(); i++) {
            inv[i].nl = discrete[inv[i].l];
            inv[i].nr = discrete[inv[i].r];
            while (!ninv.empty() && ninv.back().nl <= inv[i].nl && inv[i].nr <= ninv.back().nr) {
                ninv.pop_back();
            }
            ninv.push_back(inv[i]);
        }

        for (int i = 0, j = 0; i < idx; i++) {
            while (j < (int)ninv.size() && i > ninv[j].nl) j++;
            if (j == (int)ninv.size()) break;
            f[0][i] = ninv[j].nr;
        }
        for (int i = 1; i <= 20; i++) {
            for (int j = 0; j < idx; j++) {
                if (f[i - 1][j] < idx) {
                    f[i][j] = f[i - 1][f[i - 1][j]];
                }
            }
        }

        for (int i = 0; i < (int)query.size(); i++) {
            int l = discrete[query[i].l];
            int r = discrete[query[i].r];
            int ans = 0;
            for (int j = 20; j >= 0; j--) {
                if (f[j][l] <= r) {
                    ans |= 1 << j;
                    l = f[j][l];
                }
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}

