/*
 *  SRC: HDOJ 4339
 * PROB: Query
 * ALGO: Segment tree
 * DATE: Aug 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000010;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return LC(x) | 1; }

class Segment_tree {
    private:
        struct Tnode {
            int a, b;
            int l, r;
        };
        Tnode node[MAXN << 2];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx].a = a;
            node[idx].b = b;
            node[idx].l = node[idx].r = 0;

            if (a + 1 < b) {
                build(a, (a + b) >> 1, LC(idx));
                build((a + b) >> 1, b, RC(idx));
            }
        }

        void insert(int c, int d, int v, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) { // find the point to modify
                node[idx].l = node[idx].r = v;
                return ;
            }

            if (c < (node[idx].a + node[idx].b) >> 1) insert(c, d, v, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) insert(c, d, v, RC(idx));
            node[idx].l = node[LC(idx)].l;
            node[idx].r = node[RC(idx)].r;
            if (node[LC(idx)].l == node[LC(idx)].b - node[LC(idx)].a) node[idx].l += node[RC(idx)].l;
            if (node[RC(idx)].r == node[RC(idx)].b - node[RC(idx)].a) node[idx].r += node[LC(idx)].r;
        }

        int query(int x, int idx = 1)
        {
            if (node[idx].a == x && x + 1 == node[idx].b) {
                return node[idx].l;
            }

            int res = 0;
            if (x < node[LC(idx)].b && node[LC(idx)].r && node[LC(idx)].b - node[LC(idx)].r <= x) {
                res = node[LC(idx)].b - x + node[RC(idx)].l;
            } else if (node[idx].l && node[idx].a + node[idx].l - 1 >= x) {
                res = node[idx].a + node[idx].l - x;
            } else if (x < (node[idx].a + node[idx].b) >> 1) {
                res = query(x, LC(idx));
            } else {
                res = query(x, RC(idx));
            }
            return res;
        }
} st;

char s[2][MAXN];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case %d:\n", task);

        scanf("%s%s", s[0], s[1]);
        int len[2] = { (int)strlen(s[0]), (int)strlen(s[1]) };
        int mnlen = min(len[0], len[1]);
        int mxlen = max(len[0], len[1]);
        st.build(0, mxlen);
        for (int i = 0; i < mnlen; i++) {
            st.insert(i, i + 1, s[0][i] == s[1][i]);
        }
        for (int i = mnlen; i < mxlen; i++) {
            st.insert(i, i + 1, 0);
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int opr;
            scanf("%d", &opr);
            if (opr == 1) {
                int a, i;
                char c;
                scanf("%d%d %c", &a, &i, &c);
                a--;
                s[a][i] = c;
                st.insert(i, i + 1, s[a][i] == s[a ^ 1][i]);
            } else {
                int i;
                scanf("%d", &i);
                int r = st.query(i);
                assert(r >= 0);
                printf("%d\n", r);
            }
        }
    }

    return 0;
}

