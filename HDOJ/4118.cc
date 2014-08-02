/*
 *  SRC: HDOJ 4118
 * PROB: Holiday's Accommodation
 * ALGO: Tree dp
 * DATE: Sep 18, 2012
 * COMP: VC++
 *
 * Created by Leewings Ng
 */

#pragma comment(linker, "/STACK:102400000,102400000")

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100010;

struct Edge {
    int v, d;
    Edge(int _v, int _d) : v(_v), d(_d) { }
};
vector<Edge> e[MAXN];
int size[MAXN];
int n;
long long ans;

int getsize(int u, int parent)
{
    size[u] = 1;
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i].v;
        if (v == parent) continue;
        size[u] += getsize(v, u);
        ans += 2ll * e[u][i].d * min(size[v], n - size[v]);
    }
    return size[u];
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) e[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            e[u].push_back(Edge(v, d));
            e[v].push_back(Edge(u, d));
        }
        ans = 0;
        getsize(1, -1);
        printf("Case #%d: %I64d\n", task, ans);
    }

    return 0;
}
