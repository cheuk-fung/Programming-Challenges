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

int getFather(int u)
{
    if (fa[u] == u) return u;

    return fa[u] = getFather(fa[u]);
}

void dsUnion(int u, int v)
{
    int x = getFather(u);
    int y = getFather(v);
    if (x != y) fa[x] = y;
}

bool solve()
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

    int ans = 0;
    for (int i = 0; i < cnt; i++)
        if (getFather(edge[i].u) != getFather(edge[i].v)) {
            dsUnion(edge[i].u, edge[i].v);
            ans += edge[i].d;
        }

    printf("%d\n", ans);

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}

