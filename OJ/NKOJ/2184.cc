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
#include <cctype>
#include <algorithm>

using std::sort;

const int MAX_N = 10000;
const int MAX_M = 100000;

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

inline int next_int()
{
    char c;
    while (!isdigit(c = getchar())) ;
    int res = c - '0';
    while (isdigit(c = getchar()))
        res = res * 10 + c - '0';
    return res;
}

int main()
{
    int n, m;
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        e[i].u = next_int() - 1;
        e[i].v = next_int() - 1;
        e[i].d = next_int();
    }

    sort(e, e + m);

    int sum = 0;
    for (int i = 0; i < m; i++)
        if (get_father(e[i].u) != get_father(e[i].v)) {
            ds_union(e[i].u, e[i].v);
            sum += e[i].d;
        }

    printf("%d\n", sum);

    return 0;
}
