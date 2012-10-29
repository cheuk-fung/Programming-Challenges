/*
 *  SRC: HDOJ 4435
 * PROB: charge-station
 * ALGO: NULL
 * DATE: Oct 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>

using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
} pnt[128];

int n, d;
bool build[128], vis[128];

inline double SQR(double x) { return x * x; }
inline double dist(int a, int b) { return ceil(sqrt(SQR(pnt[a].x - pnt[b].x) + SQR(pnt[a].y - pnt[b].y))); }

bool check(int x)
{
    queue<int> Q;
    Q.push(0);
    memset(vis, 0, sizeof vis);
    vis[0] = true;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 1; i < n; i++) {
            if (vis[i]) continue;
            if (dist(u, i) - eps <= d && (build[i] || i < x)) {
                vis[i] = true;
                Q.push(i);
            } else if (dist(u, i) - eps <= d / 2.0) {
                vis[i] = true;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (!vis[i]) return false;
    }
    return true;
}

int main()
{
    while (~scanf("%d%d", &n, &d)) {
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &pnt[i].x, &pnt[i].y);
        }

        if (!check(n)) {
            puts("-1");
            continue;
        }

        memset(build, 0, sizeof build);
        for (int i = n - 1, first = 1; i > 0; i--) {
            build[i] = !check(i);
            if (build[i]) {
                putchar('1');
                first = 0;
            } else if (!first) {
                putchar('0');
            }
        }
        puts("1");
    }

    return 0;
}

