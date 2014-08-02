/*
 *  SRC: HDOJ 4282
 * PROB: A very hard mathematic problem
 * ALGO: Enumeration + Bisection
 * DATE: Sep 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>

long long gpow(long long a, long long b)
{
    long long r = 1;
    while (b) {
        if (b & 1) r *= a;
        a *= a;
        b >>= 1;
    }
    return r;
}

int main()
{
    int k;
    while (scanf("%d", &k), k) {
        int cnt = 0;
        for (int z = 2; z < 31; z++) {
            int last = pow(k, 1.0 / z) + 1;
            for (int x = 1; x <= last; x++) {
                int l = x + 1, r = last + 1;
                int y;
                while (l < r) {
                    y = (l + r) >> 1;
                    long long a = gpow(x, z), b = gpow(y, z), c = (long long)x * y * z;
                    long long now = a + b + c;
                    if (now == k) break;
                    if (now > k) r = y;
                    else l = y + 1;
                }
                long long a = gpow(x, z), b = gpow(y, z), c = (long long)x * y * z;
                long long now = a + b + c;
                if (now == k) {
                    // printf("%d %d %d\n", x, y, z);
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}

