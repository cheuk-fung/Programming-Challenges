/*
 *  SRC: HDOJ 3696
 * PROB: Farm Game
 * ALGO: Memorize DP
 * DATE: Oct 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, m;
double cost[10010], w[10010];
double dp[10010];
bool vis[10010];

struct Edge {
    int v;
    double b;
    Edge *next;
} buf[100000];
Edge *e[10010],
     *buf_tail;

void add_edge(int u, int v, double b)
{
    buf_tail->v = v;
    buf_tail->b = b;
    buf_tail->next = e[u];
    e[u] = buf_tail++;
}

inline double fmax(double a, double b) { return a > b ? a : b; }

double search(int u)
{
    if (vis[u]) return dp[u];
    vis[u] = 1;

    double res = cost[u];
    Edge *p = e[u];
    while (p) {
        double tmp = search(p->v);
        res = fmax(res, tmp * p->b);
        p = p->next;
    }

    return dp[u] = res;
}

void work()
{
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    memset(buf, 0, sizeof(buf));
    memset(e, 0, sizeof(e));
    buf_tail = buf;

    for (int i = 0; i < n; i++)
        scanf("%lf%lf", cost + i, w + i);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int k, a1, a2;
        double b;
        scanf("%d", &k);
        scanf("%d", &a1);
        for (int j = 1; j < k; j++) {
            scanf("%lf%d", &b, &a2);
            add_edge(a1 - 1, a2 - 1, b);
            int t = a1;
            a1 = a2;
            a2 = t;
        }
    }

    for (int i = 0; i < n; i++)
        if (!vis[i]) search(i);

    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += dp[i] * w[i];

    printf("%.2lf\n", ans);
}

int main()
{
    while (scanf("%d", &n), n) work();

    return 0;
}
