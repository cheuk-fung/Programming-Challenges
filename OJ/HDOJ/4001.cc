/*
 *  SRC: HDOJ 4001
 * PROB: To Miss Our Children Time
 * ALGO: Topological
 * DATE: Sep 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct Block {
    long long a, b, c;
    int d;

    bool operator<(const Block &o) const { return d == o.d ? a == o.a ? b < o.b : a < o.a : d < o.d; }
} blk[1010], nblk[1010];

int mat[1010][1010];
int indeg[1010];
long long f[1010];

inline bool above(const Block &x, const Block &y)
{
    return (y.d == 0 && y.a >= x.a && y.b >= x.b) || (y.d == 1 && y.a >= x.a && y.b >= x.b && y.a * y.b > x.a * x.b) || (y.d == 2 && y.a > x.a && y.b > x.b);
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            if (a < b) swap(a, b);
            blk[i] = (Block){a, b, c, d};
        }
        sort(blk, blk + n);
        int cnt = 0;
        nblk[cnt++] = blk[0];
        for (int i = 1; i < n; i++) {
            if (blk[i].d == 0 && blk[i].a == blk[i - 1].a && blk[i].b == blk[i - 1].b) {
                nblk[cnt - 1].c += blk[i].c;
            } else {
                nblk[cnt++] = blk[i];
            }
        }

        memset(mat, 0xff, sizeof mat);
        memset(indeg, 0, sizeof indeg);
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                if (i == j) continue;
                if (above(nblk[i], nblk[j])) {
                    mat[i][j] = nblk[j].c;
                    indeg[j]++;
                }
            }
        }

        queue<int> que;
        memset(f, 0, sizeof f);
        for (int i = 0; i < cnt; i++) {
            if (indeg[i] == 0) {
                que.push(i);
                f[i] = nblk[i].c;
            }
        }

        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (int i = 0; i < cnt; i++) {
                if (mat[now][i] > -1) {
                    f[i] = max(f[i], f[now] + mat[now][i]);
                    if (--indeg[i] == 0) {
                        que.push(i);
                    }
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < cnt; i++) {
            ans = max(ans, f[i]);
        }
        printf("%I64d\n", ans);
    }

    return 0;
}

