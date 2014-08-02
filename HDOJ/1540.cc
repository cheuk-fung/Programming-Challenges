/*
 *  SRC: HDOJ 1540
 * PROB: Tunnel Warfare
 * ALGO: Segment tree
 * DATE: Aug 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <stack>

using namespace std;

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int l, r;
        } node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            int mid = (a + b) >> 1;
            node[idx].l = node[LC(idx)].l + (node[LC(idx)].l == mid - a) * node[RC(idx)].l;
            node[idx].r = node[RC(idx)].r + (node[RC(idx)].r == b - mid) * node[LC(idx)].r;
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int x, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a == x && x + 1 == b) {
                node[idx].l = node[idx].r = v;
                return ;
            }

            int mid = (a + b) >> 1;
            if (x < mid) update(x, v, a, mid, LC(idx));
            else update(x, v, mid, b, RC(idx));
            push_up(a, b, idx);
        }

        int query(int x, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) return node[idx].l;
            if (a + node[idx].l > x) return node[idx].l;
            if (b - node[idx].r <= x) return node[idx].r;

            int mid = (a + b) >> 1;
            if ((x < mid && mid - node[LC(idx)].r <= x) || (x >= mid && mid + node[RC(idx)].l > x)) return node[LC(idx)].r + node[RC(idx)].l;
            if (x < mid) return query(x, a, mid, LC(idx));
            return query(x, mid, b, RC(idx));
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        st.build(1, n + 1);
        for (int i = 1; i <= n; i++) {
            st.update(i, 1);
        }

        stack<int> last;
        while (m--) {
            char c;
            int x;
            scanf(" %c", &c);
            if (c != 'R') scanf("%d", &x);
            if (c == 'D') {
                st.update(x, 0);
                last.push(x);
            } else if (c == 'Q') {
                int r = st.query(x);
                printf("%d\n", r);
            } else {
                st.update(last.top(), 1);
                last.pop();
            }
        }
    }

    return 0;
}

