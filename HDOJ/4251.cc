/*
 *  SRC: HDOJ 4251
 * PROB: The Famous ICPC Team Again
 * ALGO: Partition Tree
 * DATE: Jul 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

class Partition_Tree {
    private:
        struct Tnode {
            int l, r;
        };
        Tnode node[MAXN << 2];

        int l_cnt[20][MAXN], seg[20][MAXN];

        void _build(int a, int b, int d, int idx)
        {
            node[idx].l = a;
            node[idx].r = b;

            int mid = (a + b - 1) / 2, l_same_to_mid = mid - a + 1;
            for (int i = a; i < b; i++)
                if (seg[d][i] < sorted[mid]) l_same_to_mid--;

            int l_pos = a, r_pos = mid + 1;
            for (int i = a; i < b; i++) {
                l_cnt[d][i] = i == a ? 0 : l_cnt[d][i - 1];
                if (seg[d][i] < sorted[mid]) {
                    l_cnt[d][i]++;
                    seg[d + 1][l_pos++] = seg[d][i];
                } else if (seg[d][i] > sorted[mid]) {
                    seg[d + 1][r_pos++] = seg[d][i];
                } else if (l_same_to_mid > 0) {
                    l_same_to_mid--;
                    l_cnt[d][i]++;
                    seg[d + 1][l_pos++] = seg[d][i];
                } else {
                    seg[d + 1][r_pos++] = seg[d][i];
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

            int l_d = a == node[idx].l ? 0 : l_cnt[d][a - 1];
            int l_seg = l_cnt[d][b - 1] - l_d;
            if (l_seg >= k) {
                return _query(node[idx].l + l_d, node[idx].l + l_d + l_seg, k, d + 1, idx << 1);
            }

            int mid = (node[idx].l + node[idx].r - 1) >> 1;
            int r_d = a - node[idx].l - l_d;
            int r_seg = b - a - l_seg;
            return _query(mid + r_d + 1, mid + r_d + r_seg + 1, k - l_seg, d + 1, (idx << 1) + 1);
        }

    public:
        int sorted[MAXN];

        void build(int a, int b)
        {
            memcpy(seg[0], sorted, sizeof(int) * (b - a));
            sort(sorted, sorted + b - a);
            _build(a, b, 0 ,1);
        }

        int query(int a, int b, int k)
        {
            return _query(a, b, k, 0, 1);
        }
};
Partition_Tree pt;

int main()
{
    int task = 1;
    int n, m;
    while (~scanf("%d", &n)) {
        printf("Case %d:\n", task++);

        for (int i = 0; i < n; i++) scanf("%d", &pt.sorted[i]);
        pt.build(0, n);

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", pt.query(l - 1, r, (r - l) / 2 + 1));
        }
    }

    return 0;
}

