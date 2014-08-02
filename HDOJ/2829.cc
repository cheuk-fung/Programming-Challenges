/*
 *  SRC: HDOJ 2829
 * PROB: Lawrence
 * ALGO: DP
 * DATE: Aug 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

const int MAXN = 1010;

long long sum[MAXN], sqrsum[MAXN];
long long f[MAXN][MAXN];
int que[MAXN];
int now;

inline long long X(int k) { return sum[k]; }
inline long long Y(int k) { return f[now - 1][k] + (sum[k] * sum[k] + sqrsum[k]) / 2; }
inline long long KEY(int k, int j) { return f[now - 1][k] + ((sum[j] - sum[k]) * (sum[j] - sum[k]) - (sqrsum[j] - sqrsum[k])) / 2; }
inline long long cross(int o, int a, int b) { return (X(a) - X(o)) * (Y(b) - Y(o)) - (Y(a) - Y(o)) * (X(b) - X(o)); }

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);
            sum[i] = sum[i - 1] + a;
            sqrsum[i] = sqrsum[i -1 ] + a * a;
        }

        for (int j = 1; j <= n; j++) {
            f[0][j] = (sum[j] * sum[j] - sqrsum[j]) / 2;
        }
        for (now = 1; now <= m; now++) {
            int head = 0, tail = 0;
            que[tail++] = 0;
            for (int j = 1; j <= n; j++) {
                while (head + 1 < tail && KEY(que[head], j) >= KEY(que[head + 1], j)) head++;
                f[now][j] = KEY(que[head], j);
                // printf("%d %d %d\n", now, j, f[now][j]);

                while (head + 1 < tail && cross(que[tail - 2], que[tail - 1], j) <= 0) tail--;
                que[tail++] = j;
            }
        }

        // printf("%lld\n", f[m][n]);
        printf("%I64d\n", f[m][n]);
    }

    return 0;
}

