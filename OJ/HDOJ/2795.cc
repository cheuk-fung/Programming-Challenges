/*
 *  SRC: HDOJ 2795
 * PROB: Billboard
 * ALGO: Segment tree
 * DATE: Aug 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

class Segment_tree {
    private:
        static int lep, rep;
        int mx[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }
        void push_up(int idx) { mx[idx] = max(mx[LC(idx)], mx[RC(idx)]); }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(mx, 0, sizeof mx);
        }

        void update(int x, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (x == a && x + 1 == b) {
                mx[idx] += v;
                return ;
            }

            int mid = (a + b) >> 1;
            if (x < mid) update(x, v, a, mid, LC(idx));
            else update(x, v, mid, b, RC(idx));
            push_up(idx);
        }

        int query(int v, int a = lep, int b = rep, int idx = 1)
        {
            if (v > mx[idx]) return -1;
            if (a + 1 == b) {
                return b;
            }

            int mid = (a + b) >> 1;
            if (v <= mx[LC(idx)]) return query(v, a, mid, LC(idx));
            return query(v, mid, b, RC(idx));
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int h, w, n;
    while (~scanf("%d%d%d", &h, &w, &n)) {
        st.build(0, min(n, h));
        for (int i = 0; i < min(n, h); i++) {
            st.update(i, w);
        }

        for (int i = 0; i < n; i++) {
            int wi;
            scanf("%d", &wi);
            int r = st.query(wi);
            printf("%d\n", r);
            if (r > 0) {
                st.update(r - 1, -wi);
            }
        }
    }

    return 0;
}

