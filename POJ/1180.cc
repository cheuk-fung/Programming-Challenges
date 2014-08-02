/*
 *  SRC: POJ 1180
 * PROB: Batch Scheduling
 * ALGO: DP
 * DATE: Aug 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

const int MAXN = 10010;

long long f[MAXN], Tsum[MAXN], Fsum[MAXN];
int que[MAXN];
int n, s, now;

inline long long MIN(int a, int b) { return a < b ? a : b; }
inline long long X(int k) { return Fsum[k]; }
inline long long Y(int k) { return f[k] - (Fsum[n] - Fsum[k]) * Tsum[k] - s * Fsum[k]; }
inline long long KEY(int k, int i) { return f[k] + (Fsum[n] - Fsum[k]) * (s + Tsum[i] - Tsum[k]); }
inline long long cross(int o, int a, int b) { return (X(a) - X(o)) * (Y(b) - Y(o)) - (Y(a) - Y(o)) * (X(b) - X(o)); }

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++) {
        int T, F;
        scanf("%d%d", &T, &F);
        Tsum[i] = Tsum[i - 1] + T;
        Fsum[i] = Fsum[i - 1] + F;
    }

    int head = 0, tail = 0;
    que[tail++] = 0;
    for (int i = 1; i <= n; i++) {
        while (head + 1 < tail && KEY(que[head], i) >= KEY(que[head + 1], i)) head++;
        f[i] = KEY(que[head], i);

        while (head + 1 < tail && cross(que[tail - 2], que[tail - 1], i) <= 0) tail--;
        que[tail++] = i;
    }

    printf("%lld\n", f[n]);

    return 0;
}

