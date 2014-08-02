/*
 *  SRC: HDOJ 3507
 * PROB: Print Artical
 * ALGO: DP
 * DATE: Aug 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

const int MAXN = 500010;

long long sum[MAXN], f[MAXN];
int que[MAXN];

inline long long X(int k) { return sum[k]; }
inline long long Y(int k) { return f[k] + sum[k] * sum[k]; }

inline long long cross(int o, int a, int b) { return (X(a) - X(o)) * (Y(b) - Y(o)) - (Y(a) - Y(o)) * (X(b) - X(o)); }
inline long long key(int k, int i) { return f[k] + (sum[i] - sum[k]) * (sum[i] - sum[k]); }

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);
            sum[i] = sum[i - 1] + a;
        }

        int head = 0, tail = 0;
        que[tail++] = 0;
        for (int i = 1; i <= n; i++) {
            while (head + 1 < tail && key(que[head], i) >= key(que[head + 1], i)) head++;
            f[i] = key(que[head], i) + m;

            while (head + 1 < tail && cross(que[tail - 2], que[tail - 1], i) <= 0) tail--;
            que[tail++] = i;
        }

        // printf("%lld\n", f[n]);
        printf("%I64d\n", f[n]);
    }

    return 0;
}

