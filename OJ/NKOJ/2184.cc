/*
 *  SRC: NKOJ 2184
 * PROB: Exercise 4 最小生成树
 * ALGO: Kruskal
 * DATE: Nov 09, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

const int MAX_N = 10010;
const int MAX_M = 100010;

struct Edge
{
    int u, v, d;

    bool operator < (const Edge& other) const { return d < other.d; }
} e[MAX_M];

int fa[MAX_N];

int get_father(int u)
{
    if (fa[u] == u) return u;

    return fa[u] = get_father(fa[u]);
}

void ds_union(int u, int v)
{
    int x = get_father(u);
    int y = get_father(v);
    if (x != y) fa[x] = y;
}

int kruskal(int m)
{
    sort(e, e + m);

    int sum = 0;
    for (int i = 0; i < m; i++)
        if (get_father(e[i].u) != get_father(e[i].v)) {
            ds_union(e[i].u, e[i].v);
            sum += e[i].d;
        }

    return sum;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) fa[i] = i;
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            u--; v--;
            e[i] = (Edge){u, v, d};
        }

        printf("%d\n", kruskal(m));
    }

    return 0;
}

