/*
 *  SRC: HDOJ 3480
 * PROB: Division
 * ALGO: DP
 * DATE: Aug 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10010;

int a[MAXN];
long long f[2][MAXN];

struct Point {
    long long x, y;
};
Point que[MAXN];

inline long long cross(const Point &o, const Point &a, const Point &b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline long long key(const Point &a, const Point &b)
{
    return a.y - 2 * b.x * a.x + b.x * b.x;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        sort(a + 1, a + n + 1);

        for (int i = 1; i <= n; i++) {
            f[1][i] = (a[i] - a[1]) * (a[i] - a[1]);
        }
        for (int i = 2; i <= m; i++) {
            int head = 0, tail = 0;
            for (int j = 1; j <= n; j++) {
                Point now = {a[j], f[(i - 1) & 1][j - 1] + a[j] * a[j]};
                while (head + 1 < tail && cross(que[tail - 2], que[tail - 1], now) <= 0) tail--;
                que[tail++] = now;

                while (head + 1 < tail && key(que[head], now) >= key(que[head + 1], now)) head++;
                f[i & 1][j] = que[head].y - 2 * a[j] * que[head].x + a[j] * a[j];
                // printf("%d %d %lld\n", i, j, f[i & 1][j]);
            }
        }

        // printf("Case %d: %lld\n", task, f[m & 1][n]);
        printf("Case %d: %I64d\n", task, f[m & 1][n]);
    }

    return 0;
}
