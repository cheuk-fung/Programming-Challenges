/*
 *  SRC: ZOJ 3632
 * PROB: Watermelon Full of Water
 * ALGO: Segment Tree
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 50010;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return LC(x) | 1; }

class Segment_Tree {
    private:
        struct TNode {
            int a, b;
            long long mn;
            int cover;
        } node[MAXN << 2];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx] = (TNode){a, b, LLINF, false};
            if (a + 1 < b) {
                build(a, (a + b) >> 1, LC(idx));
                build((a + b) >> 1, b, RC(idx));
            }
        }

        void insert(int c, int d, long long v, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                if (node[idx].cover || v <= node[idx].mn) {
                    node[idx].mn = min(node[idx].mn, v);
                    node[idx].cover = true;
                    return ;
                }
            }

            if (node[idx].cover) {
                node[idx].cover = false;
                node[LC(idx)].cover = node[RC(idx)].cover = true;
                node[LC(idx)].mn = node[idx].mn;
                node[RC(idx)].mn = node[idx].mn;
            }

            if (c < (node[idx].a + node[idx].b) >> 1) insert(c, d, v, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) insert(c, d, v, RC(idx));

            node[idx].mn = min(node[LC(idx)].mn, node[RC(idx)].mn);
            node[idx].cover = (node[LC(idx)].mn == node[RC(idx)].mn) && node[LC(idx)].cover && node[RC(idx)].cover;
        }

        long long query(int c, int d, int idx = 1)
        {
            if ((c <= node[idx].a && node[idx].b <= d) || node[idx].cover) {
                return node[idx].mn;
            }

            long long lmn = LLINF, rmn = LLINF;
            if (c < (node[idx].a + node[idx].b) >> 1) lmn = query(c, d, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) rmn = query(c, d, RC(idx));
            return min(lmn, rmn);
        }
} st;

int price[MAXN];
int day[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        st.build(0, n + 1);
        st.insert(0, 1, 0);
        for (int i = 1; i <= n; i++) scanf("%d", price + i);
        for (int i = 1; i <= n; i++) scanf("%d", day + i);
        for (int i = 1; i <= n; i++) {
            long long r = min(st.query(i - 1, i), st.query(i, i + 1));
            st.insert(i, min(i + day[i], n + 1), r + price[i]);
        }
        printf("%lld\n", st.query(n, n + 1));
    }


    return 0;
}
