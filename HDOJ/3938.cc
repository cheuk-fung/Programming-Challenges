/*
 *  SRC: HDOJ 3938
 * PROB: Portal
 * ALGO: Disjoint Set
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

struct Edge {
    int u, v, c;

    bool operator<(const Edge &o) const
    {
        return c < o.c;
    }
};
Edge e[50010];

struct Query {
    int q, id;
    int cnt;
};
Query l[10010];

bool sort_q(const Query &a, const Query &b)
{
    return a.q < b.q;
}

bool sort_id(const Query &a, const Query &b)
{
    return a.id < b.id;
}

class DisjointSet {
    private:

    public:
        int p[10010]; // parent

        DisjointSet()
        {
            reset();
        }

        void reset()
        {
            memset(p, 0xff, sizeof(p));
        }

        int find(int u)
        {
            if (p[u] < 0) return u;
            return p[u] = find(p[u]);
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) {
                p[x] += p[y];
                p[y] = x;
            }
        }
};
DisjointSet ds;

int main()
{
    int n, m, q;
    while (~scanf("%d%d%d", &n, &m, &q)) {
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
        }
        sort(e, e + m);

        for (int i = 0; i < q; i++) {
            scanf("%d", &l[i].q);
            l[i].id = i;
        }
        sort(l, l + q, sort_q);

        int cnt = 0;
        for (int i = 0, j = 0; i < q; i++) {
            while (j < m && e[j].c <= l[i].q) {
                int x = ds.find(e[j].u);
                int y = ds.find(e[j].v);
                if (x != y) {
                    cnt += ds.p[x] * ds.p[y];
                    ds.join(e[j].u, e[j].v);
                }
                j++;
            }
            l[i].cnt = cnt;
        }

        sort(l, l + q, sort_id);
        for (int i = 0; i < q; i++) {
            printf("%d\n", l[i].cnt);
        }

        ds.reset();
    }

    return 0;
}

