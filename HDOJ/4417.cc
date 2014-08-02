/*
 *  SRC: HDOJ 4417
 * PROB: Super Mario
 * ALGO: Merge tree
 * DATE: Sep 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

class Tree {
    private:
        static int lep, rep;

        int buf[MAXN * 20];
        int *buftail;

        int *h[MAXN << 2];

        int LC(int x) const { return x << 1; }
        int RC(int x) const { return x << 1 | 1; }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            buftail = buf;
        }

        void insert(int p, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                h[idx] = buftail++;
                *h[idx] = v;
                return ;
            }

            int mid = (a + b) >> 1;
            if (p < mid) return insert(p, v, a, mid, LC(idx));
            insert(p, v, mid, b, RC(idx));
        }

        void merge(int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) return ;

            int mid = (a + b) >> 1;
            merge(a, mid, LC(idx));
            merge(mid, b, RC(idx));

            h[idx] = buftail;
            buftail += b - a;
            std::merge(h[LC(idx)], h[LC(idx)] + mid - a, h[RC(idx)], h[RC(idx)] + b - mid, h[idx]);
        }

        int query(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return upper_bound(h[idx], h[idx] + b - a, v) - h[idx];
            }

            int mid = (a + b) >> 1;
            int r = 0;
            if (c < mid) r += query(c, d, v, a, mid, LC(idx));
            if (d > mid) r += query(c, d, v, mid, b, RC(idx));
            return r;
        }
} tree;
int Tree::lep, Tree::rep;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, m;
        scanf("%d%d", &n, &m);
        tree.build(0, n);
        for (int i = 0; i < n; i++) {
            int h;
            scanf("%d", &h);
            tree.insert(i, h);
        }
        tree.merge();

        printf("Case %d:\n", task);
        for (int i = 0; i < m; i++) {
            int l, r, h;
            scanf("%d%d%d", &l, &r, &h);
            printf("%d\n", tree.query(l, r + 1, h));
        }
    }

    return 0;
}

