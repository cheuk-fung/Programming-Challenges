/*
 *  SRC: ZOJ 3635
 * PROB: Cinema in Akiba
 * ALGO: Segment tree
 * DATE: Aug 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        int cnt[MAXN << 2];
        int last[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                cnt[idx] = v;
                if (v) last[idx] = a;
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, v, a, mid, LC(idx));
            else update(c, v, mid, b, RC(idx));
            cnt[idx] = cnt[LC(idx)] + cnt[RC(idx)];
            if (cnt[RC(idx)]) last[idx] = last[RC(idx)];
            else last[idx] = last[LC(idx)];
        }

        int query(int v, int a = lep, int b = rep, int idx = 1)
        {
            if (cnt[idx] == v) return last[idx];

            int mid = (a + b) >> 1;
            if (cnt[LC(idx)] >= v) return query(v, a, mid, LC(idx));
            return query(v - cnt[LC(idx)], mid, b, RC(idx));
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int ans[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        st.build(0, n);
        for (int i = 0; i < n; i++) {
            st.update(i, 1);
        }
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            int pos = st.query(a);
            ans[i] = pos + 1;
            st.update(pos, 0);
        }

        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int q;
            scanf("%d", &q);
            printf("%d%c", ans[q - 1], i + 1 == m ? '\n' : ' ');
        }
    }

    return 0;
}

