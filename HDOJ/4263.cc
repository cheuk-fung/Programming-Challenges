/*
 *  SRC: HDOJ 4263
 * PROB: Red/Blue Spanning Tree
 * ALGO: Spanning Tree
 * DATE: Aug 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 1010;

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
} ds;

vector<pii> R, B;

int main()
{
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        R.clear();
        B.clear();
        for (int i = 0; i < m; i++) {
            char c;
            int u, v;
            scanf(" %c%d%d", &c, &u, &v);
            if (c == 'R') R.push_back(pii(u, v));
            else B.push_back(pii(u, v));
        }

        ds.build();
        int lo = 0;
        for (int i = 0; i < (int)R.size(); i++) {
            if (ds.find(R[i].first) != ds.find(R[i].second)) {
                ds.join(R[i].first, R[i].second);
            }
        }
        for (int i = 0; i < (int)B.size(); i++) {
            if (ds.find(B[i].first) != ds.find(B[i].second)) {
                ds.join(B[i].first, B[i].second);
                lo++;
            }
        }

        ds.build();
        int hi = 0;
        for (int i = 0; i < (int)B.size(); i++) {
            if (ds.find(B[i].first) != ds.find(B[i].second)) {
                ds.join(B[i].first, B[i].second);
                hi++;
            }
        }

        puts(lo <= k && k <= hi ? "1" : "0");
    }

    return 0;
}

