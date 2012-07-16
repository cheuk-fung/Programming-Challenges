/*
 *  SRC: POJ 2104
 * PROB: K-th Number
 * ALGO: Partition Tree
 * DATE: Sep 08, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

const int MAXN = 100010;

class Partition_Tree {
    private:
        struct Tnode {
            int l, r;
        };
        Tnode node[MAXN << 2];

        int lcnt[20][MAXN], seg[20][MAXN];

        void _build(int a, int b, int d, int idx)
        {
            node[idx].l = a;
            node[idx].r = b;

            int mid = (a + b - 1) >> 1;
            int lmid = mid - a + 1; // the number of numbers which equal sorted[mid]
            for (int i = a; i < b; i++) {
                if (seg[d][i] < sorted[mid]) lmid--;
            }

            int lpos = a, rpos = mid + 1;
            for (int i = a; i < b; i++) {
                lcnt[d][i] = (i == a ? 0 : lcnt[d][i - 1]);
                if (seg[d][i] < sorted[mid]) {
                    lcnt[d][i]++;
                    seg[d + 1][lpos++] = seg[d][i];
                } else if (seg[d][i] > sorted[mid]) {
                    seg[d + 1][rpos++] = seg[d][i];
                } else if (lmid > 0) {
                    lmid--;
                    lcnt[d][i]++;
                    seg[d + 1][lpos++] = seg[d][i];
                } else {
                    seg[d + 1][rpos++] = seg[d][i];
                }
            }

            if (a + 1 < b) {
                _build(a, mid + 1, d + 1, idx << 1);
                _build(mid + 1, b, d + 1, (idx << 1) + 1);
            }
        }

        int _query(int a, int b, int k, int d, int idx)
        {
            if (b - a == 1) return seg[d][a];

            int ld = (a == node[idx].l ? 0 : lcnt[d][a - 1]),
                lseg = lcnt[d][b - 1] - ld;
            if (lseg >= k) {
                return _query(node[idx].l + ld, node[idx].l + ld + lseg, k, d + 1, idx << 1);
            }

            int mid = (node[idx].l + node[idx].r - 1) >> 1,
                rd = a - node[idx].l - ld,
                rseg = b - a - lseg;
            return _query(mid + rd + 1, mid + rd + rseg + 1, k - lseg, d + 1, (idx << 1) + 1);
        }

    public:
        int sorted[MAXN];

        void build(int a, int b)
        {
            memcpy(seg[0], sorted, sizeof(int) * (b - a));
            sort(sorted, sorted + b - a);
            _build(a, b, 0, 1);
        }

        int query(int a, int b, int k)
        {
            return _query(a, b, k, 0, 1);
        }
};

Partition_Tree pt;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &pt.sorted[i]);
    pt.build(0, n);

    for (int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", pt.query(l - 1, r, k));
    }

    return 0;
}
