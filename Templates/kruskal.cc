/*
 *  SRC: POJ 1258
 * PROB: Agri-Net
 * ALGO: Kruskal + Disjoint Set
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

const int MAX_N = 110;
const int MAX_M = 10010;

struct Edge {
    int u, v, d;

    bool operator <(const Edge &other) const { return d < other.d; }
} e[MAX_M];

class DisjointSet {
    private:
        int p[MAX_N]; // parent

    public:
        void reset()
        {
            for (int i = 0; i < MAX_N; i++) p[i] = i;
        }

        int find(int u)
        {
            if (p[u] == u) return u;
            return p[u] = find(p[u]);
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) p[x] = y;
        }
};
DisjointSet ds;

int kruskal(int m)
{
    sort(e, e + m);

    int sum = 0;
    for (int i = 0; i < m; i++)
        if (ds.find(e[i].u) != ds.find(e[i].v)) {
            ds.join(e[i].u, e[i].v);
            sum += e[i].d;
        }

    return sum;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ds.reset();

        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int d;
                scanf("%d", &d);
                if (i < j) e[cnt++] = (Edge){i, j, d};
            }

        printf("%d\n", kruskal(cnt));
    }

    return 0;
}
