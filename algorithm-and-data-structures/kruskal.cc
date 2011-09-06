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

struct Edge
{
    int u, v, d;

    bool operator < (const Edge& other) const
    {
        return d < other.d;
    }
} edge[MAX_N * MAX_N];

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

bool kruskal()
{
    int n;
    if (scanf("%d", &n) == EOF) return false;

    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int d;
            scanf("%d", &d);
            if (i == j) fa[i] = i;
            else if (j > i) {
                edge[cnt].u = i;
                edge[cnt].v = j;
                edge[cnt].d = d;
                cnt++;
            }
        }

    sort(edge, edge + cnt);

    int sum = 0;
    for (int i = 0; i < cnt; i++)
        if (get_father(edge[i].u) != get_father(edge[i].v)) {
            ds_union(edge[i].u, edge[i].v);
            sum += edge[i].d;
        }

    printf("%d\n", sum);

    return true;
}

int main()
{
    while (kruskal()) ;

    return 0;
}

