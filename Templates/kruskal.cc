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
    int n;
    while (~scanf("%d", &n)) {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int d;
                scanf("%d", &d);
                if (i == j) fa[i] = i;
                else if (i < j)
                    e[cnt++] = (Edge){i, j, d};
            }
        
        printf("%d\n", kruskal(cnt));
    }

    return 0;
}
