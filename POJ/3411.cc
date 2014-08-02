/*
 *  SRC: POJ 3411
 * PROB: Paid Roads
 * ALGO: DFS
 * DATE: Jul 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
    int a, b, c, p, r;
} e[11];

int n, m;
int best;
int vis[11];
int route[110000];
vector<int> next[11];

int encode(int x)
{
    int res = 0;
    for (int i = 0; i < m; i++) res = res * 2 + (vis[i] ? 1 : 0);
    return res * 100 + x;
}

void search(int u, int tot)
{
    if (tot >= best) return ;
    if (u == n) {
        best = min(best, tot);
        return ;
    }

    vis[u]++;
    int code = encode(u);
    if (tot >= route[code]) {
        vis[u]--;
        return ;
    }
    route[code] = tot;

    for (int i = 0; i < next[u].size(); i++) {
        int v = next[u][i];
        if (vis[e[v].c]) search(e[v].b, tot + e[v].p);
        search(e[v].b, tot + e[v].r);
    }

    vis[u]--;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d%d", &e[i].a, &e[i].b, &e[i].c, &e[i].p, &e[i].r);
        next[e[i].a].push_back(i);
    }

    best = INF;
    memset(route, 0x3f, sizeof(route));
    search(1, 0);
    if (best == INF) {
        puts("impossible");
    } else {
        printf("%d\n", best);
    }

    return 0;
}

