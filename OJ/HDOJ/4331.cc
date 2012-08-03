/*
 *  SRC: HDOJ 4331
 * PROB: Image Recognition
 * ALGO: BIT
 * DATE: Aug 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1010;

int mat[MAXN][MAXN];

struct Point {
    int l, u, r, d;
};
Point pnt[MAXN][MAXN];
vector<pii> query;

class BIT {
    private:
        int c[MAXN];
        int lowbit(int x) { return x & -x; }

    public:
        void reset() { memset(c, 0, sizeof c); }
        void update(int x, int v) { for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ; }
        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        memset(pnt, 0, sizeof pnt);
        for (int i = 0; i < n; i++) pnt[0][i].u = mat[0][i];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j]) {
                    pnt[i][j].u = pnt[i - 1][j].u + 1;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            pnt[i][0].l = mat[i][0];
            pnt[i][n - 1].r = mat[i][n - 1];
            for (int j = 1; j < n; j++) {
                if (mat[i][j]) {
                    pnt[i][j].l = pnt[i][j - 1].l + 1;
                }
            }
            for (int j = n - 2; j >= 0; j--) {
                if (mat[i][j]) {
                    pnt[i][j].r = pnt[i][j + 1].r + 1;
                }
            }
        }
        for (int i = 0; i < n; i++) pnt[n - 1][i].d = mat[n - 1][i];
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j]) {
                    pnt[i][j].d = pnt[i + 1][j].d + 1;
                }
            }
        }

        int ans = 0;
        int offset = 10000;
        for (int k = 0; k < n << 1; k++) {
            query.clear();
            int starti = k < n ? 0 : k - n + 1;
            int startj = k < n ? k : n - 1;
            for (int i = starti, j = startj; i <= k && i < n; i++, j--) {
                if (mat[i][j]) {
                    // [i, i + min(pnt[i][j].l, pnt[i][j].d))
                    query.push_back(pii(i, i));
                    query.push_back(pii(i + min(pnt[i][j].l, pnt[i][j].d), i + offset));
                }
            }
            sort(query.begin(), query.end());

            bit.reset();
            vector<pii>::const_iterator vi = query.begin();
            for (int i = starti, j = startj; i <= k && i < n; i++, j--) {
                for ( ; vi != query.end() && i == vi->first; vi++) {
                    if (vi->second < offset) ans -= bit.sum(i + 1);
                    else ans += bit.sum(vi->second - offset + 1);
                }

                if (mat[i][j]) {
                    bit.update(i - min(pnt[i][j].u, pnt[i][j].r) + 1 + 1, 1);
                }
            }
            for ( ; vi != query.end(); vi++) {
                if (vi->second < offset) ans -= bit.sum(vi->second - offset + 1);
                else ans += bit.sum(vi->second - offset + 1);
            }
        }

        printf("Case %d: %d\n", task, ans);
    }

    return 0;
}

