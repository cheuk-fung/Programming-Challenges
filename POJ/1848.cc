/*
 *  SRC: POJ 1848
 * PROB: Tree
 * ALGO: Tree DP
 * DATE: Oct 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 110;
const int BAD = 209;

int f[MAXN], g[MAXN][MAXN], parent[MAXN], ancestor[MAXN][MAXN];
vector<int> e[MAXN];
vector<int> pnt[MAXN];
vector< vector<int> > tree[MAXN];

void dfs(int u, int p)
{
    parent[u] = p;
    pnt[u].push_back(u);
    tree[u].push_back(pnt[u]);
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v == p) continue;
        dfs(v, u);
        pnt[u].insert(pnt[u].end(), pnt[v].begin(), pnt[v].end());
        tree[u].push_back(pnt[v]);
    }
}

int getancestor(int u, int p)
{
    if (ancestor[u][p] != -1) return ancestor[u][p];

    g[u][p] = 0;
    int *cnt = &g[u][p];

    int last = u;
    while (u != p) {
        for (int i = 0; i < (int)e[u].size(); i++) {
            int v = e[u][i];
            if (v == parent[u] || v == last) continue;
            assert(f[v] != -1);
            *cnt += f[v];
        }
        last = u;
        u = parent[u];
    }

    return last;
}

int dp(int u, int p)
{
    if (f[u] != -1) return f[u];
    f[u] = BAD;

    int sum = 0;
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v == p) continue;
        sum += dp(v, u);
    }

    for (vector< vector<int> >::iterator first = tree[u].begin(); first != tree[u].end(); first++) {
        for (vector< vector<int> >::iterator second = first + 1; second != tree[u].end(); second++) {
            for (vector<int>::iterator i = first->begin(); i != first->end(); i++) {
                for (vector<int>::iterator j = second->begin(); j != second->end(); j++) {
                    if (*i == parent[*j]) continue;
                    int a = getancestor(*i, u);
                    int b = getancestor(*j, u);
                    int now = g[*i][u] + g[*j][u] + 1 + sum;
                    if (a != u) now -= f[a];
                    if (b != u) now -= f[b];
                    f[u] = min(f[u], now);
                }
            }
        }
    }

    return f[u];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(0, 0);

    memset(f, 0xff, sizeof f);
    memset(g, 0xff, sizeof g);
    memset(ancestor, 0xff, sizeof ancestor);
    int r = dp(0, 0);
    printf("%d\n", r == BAD ? -1 : r);

    return 0;
}

