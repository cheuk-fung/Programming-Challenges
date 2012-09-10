/*
 *  SRC: POJ 3164
 * PROB: Command Network
 * ALGO: Chu-Liu/Edmonds Algorithm (Directed Minimum Spanning Tree)
 * DATE: Jul 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const double DINF = 1e100;
const double eps = 1e-8;

int n, m;
double G[MAXN][MAXN];
int erase[MAXN], prev[MAXN];
int vis[MAXN];

struct Point {
    double x, y;
} ver[MAXN];

inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline double sqr(double x) { return x * x ; }
inline double dist(const Point &a, const Point &b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double solve(int root)
{
    memset(erase, 0, sizeof erase);

    double res = 0;
    bool has_circuit = false;
    do {
        for (int i = 0; i < n; i++) {
            prev[i] = i;
            if (i == root || erase[i]) continue;
            for (int j = 0; j < n; j++) {
                if (erase[j]) continue;
                if (ls(G[j][i], G[prev[i]][i])) {
                    prev[i] = j;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (i != root && !erase[i] && prev[i] == i) {
                return -1;
            }
        }

        has_circuit = false;
        memset(vis, 0xff, sizeof vis);
        for (int i = 0; i < n; i++) {
            if (i == root || erase[i]) continue;

            int curr = i;
            while (vis[curr] != i && curr != root) {
                vis[curr] = i;
                curr = prev[curr];
            }
            if (curr != i) continue;

            has_circuit = true;
            res += G[prev[curr]][curr];
            for (int j = prev[curr]; j != curr; j = prev[j]) {
                res += G[prev[j]][j];
                erase[j] = true;
            }

            int t = curr;
            do {
                for (int j = 0; j < n; j++) {
                    if (j == curr || erase[j]) continue;
                    if (!eq(G[j][t], DINF)) {
                        G[j][curr] = min(G[j][curr], G[j][t] - G[prev[t]][t]);
                    }
                    G[curr][j] = min(G[curr][j], G[t][j]);
                }
                t = prev[t];
            } while (t != curr) ;
        }
    } while (has_circuit) ;

    for (int i = 0; i < n; i++) {
        if (i != root && !erase[i]) {
            res += G[prev[i]][i];
        }
    }

    return res;
}

int main()
{
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                G[i][j] = DINF;

        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &ver[i].x, &ver[i].y);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u != v) G[u - 1][v - 1] = dist(ver[u - 1], ver[v - 1]);
        }

        double r = solve(0);
        if (r + eps > 0) {
            printf("%.2f\n", r + eps);
        } else {
            puts("poor snoopy");
        }
    }

    return 0;
}

