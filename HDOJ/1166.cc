/*
 *  SRC: HDOJ 1166
 * PROB: 敌兵布阵
 * ALGO: Segment tree
 * DATE: Aug 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep; // left endpoint and right endpoint
        int val[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int idx)
        {
            val[idx] = val[LC(idx)] + val[RC(idx)];
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(val, 0, sizeof val);
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                val[idx] += v;
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
                return val[idx];
            }

            int ans = 0, mid = (a + b) >> 1;
            if (c < mid) ans += query(c, d, a, mid, LC(idx));
            if (d > mid) ans += query(c, d, mid, b, RC(idx));
            return ans;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

char ins[100];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case %d:\n", task);

        int n;
        scanf("%d", &n);
        st.build(0, n);

        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            st.update(i, i + 1, a);
        }

        do {
            scanf("%s", ins);
            if (strcmp(ins, "End") == 0) break;

            int i, j;
            scanf("%d%d", &i, &j);
            if (ins[0] == 'A') {
                st.update(i - 1, i, j);
            } else if (ins[0] == 'S') {
                st.update(i - 1, i, -j);
            } else {
                int r = st.query(i - 1, j);
                printf("%d\n", r);
            }
        } while (true) ;
    }

    return 0;
}

