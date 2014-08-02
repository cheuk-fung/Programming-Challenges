/*
 *  SRC: HDOJ 1754
 * PROB: I Hate It
 * ALGO: Segment tree
 * DATE: Aug 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

class Segment_tree {
    private:
        static int lep, rep;
        int mx[MAXN << 4];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int idx)
        {
            mx[idx] = max(mx[LC(idx)], mx[RC(idx)]);
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                mx[idx] = v;
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));

            push_up(idx);
        }

        int query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return mx[idx];
            }

            int mid = (a + b) >> 1;
            int lres = 0, rres = 0;
            if (c < mid) lres = query(c, d, a, mid, LC(idx));
            if (d > mid) rres = query(c, d, mid, b, RC(idx));
            return max(lres, rres);
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        st.build(0, n);

        for (int i = 0; i < n; i++) {
            int grade;
            scanf("%d", &grade);
            st.update(i, i + 1, grade);
        }

        for (int i = 0; i < m; i++) {
            char opr;
            int a, b;
            scanf(" %c%d%d", &opr, &a, &b);
            if (opr == 'Q') {
                int r = st.query(a - 1, b);
                printf("%d\n", r);
            } else {
                st.update(a - 1, a, b);
            }
        }
    }

    return 0;
}

