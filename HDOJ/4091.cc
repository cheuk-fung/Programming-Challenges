/*
 *  SRC: HDOJ 4091
 * PROB: Zombie’s Treasure Chest
 * ALGO: Number Theory
 * DATE: Sep 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <algorithm>

using namespace std;

long long extended_euclid(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;

        return a;
    }

    long long r = extended_euclid(b, a % b, x, y);
    long long t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, s1, v1, s2, v2;
        scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);
        if ((long long)v1 * s2 < (long long)v2 * s1) {
            swap(s1, s2);
            swap(v1, v2);
        }
        long long x = n / s1;
        long long r = n % s1;
        long long ans = 0;
        if (x * x <= n) {
            for (long long y = 0; y <= x && n - s1 * y >= 0; y++) {
                long long now = v1 * y + v2 * ((n - s1 * y) / s2);
                // printf("%lld %lld\n", y, now);
                ans = max(ans, now);
            }
        } else {
            for (long long z = 0; z <= r; z++) {
                long long y, x;
                long long g = extended_euclid(s1, s2, &y, &x);
                if (z % g != 0) continue;
                long long y0 = y * (-z / g);
                long long mod = s2 / g;
                y = (y0 % mod + mod) % mod;
                y = n / s1 - y;
                if (y < 0 || n - s1 * y < 0) continue;
                long long now = v1 * y + v2 * ((n - s1 * y) / s2);
                // printf("%lld %lld %lld\n", z, y, now);
                ans = max(ans, now);
            }
        }
        printf("Case #%d: %I64d\n", task, ans);
    }

    return 0;
}

