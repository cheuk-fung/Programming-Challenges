/*
 *  SRC: NKOJ 2205
 * PROB: Big Macs Around the World
 * ALGO: SPFA
 * DATE: Oct 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 2012;
const long double eps = 1e-10;
const long double DINF = 1e20;

struct Edge {
    int v;
    long double d;
};
vector<Edge> e[MAXN];

long double dist[MAXN];
int inQ[MAXN], cnt[MAXN];

long double spfa(int n, int s, int t, long double price)
{
    for (int i = 0; i <= n; i++) dist[i] = DINF;

    dist[s] = 0;
    queue<int> Q;
    Q.push(s);
    inQ[s] = true;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inQ[u] = false;
        for (int i = 0; i < (int)e[u].size(); i++) {
            int v = e[u][i].v;
            long double d = e[u][i].d;
            if (dist[u] + d + eps < dist[v]) {
                dist[v] = dist[u] + d;
                if (!inQ[v]) {
                    if (++cnt[v] >= n) return 0;
                    Q.push(v);
                    inQ[v] = true;
                }
            }
        }
    }

    return price * exp(dist[t]);
}

int main()
{
    int n, m, a, b;
    long double v;
    scanf("%d%d%Lf%d%d", &n, &m, &v, &a, &b);

    for (int i = 0; i < m; i++) {
        int u, v;
        long double d;
        scanf("%d%d%Lf", &u, &v, &d);
        e[u].push_back((Edge){v, log(d)});
    }

    long double r = spfa(n, a, b, v);
    printf("%.8Lf\n", r);

    return 0;
}

