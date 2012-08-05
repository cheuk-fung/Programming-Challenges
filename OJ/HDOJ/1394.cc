/*
 *  SRC: HDOJ 1394
 * PROB: Minimum Inversion Number
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

const int MAXN = 5010;

class Segment_tree {
    private:
        static int lep, rep;
        int sum[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }
        void push_up(int idx) { sum[idx] = sum[LC(idx)] + sum[RC(idx)]; }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(sum, 0, sizeof sum);
        }

        void update(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                sum[idx] = 1;
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, a, mid, LC(idx));
            if (d > mid) update(c, d, mid, b, RC(idx));
            push_up(idx);
        }

        int query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return sum[idx];
            }

            int mid = (a + b) >> 1;
            int res = 0;
            if (c < mid) res += query(c, d, a, mid, LC(idx));
            if (d > mid) res += query(c, d, mid, b, RC(idx));
            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int permutation[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        st.build(0, n);

        for (int i = 0; i < n; i++) {
            scanf("%d", permutation + i);
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += st.query(permutation[i], n);
            st.update(permutation[i], permutation[i] + 1);
        }

        int ans = cnt;
        for (int i = 0; i < n; i++) {
            cnt += n - permutation[i] - 1 - permutation[i];
            ans = min(ans, cnt);
        }
        printf("%d\n", ans);
    }

    return 0;
}

