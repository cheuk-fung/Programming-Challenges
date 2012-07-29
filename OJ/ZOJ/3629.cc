/*
 *  SRC: ZOJ 3629
 * PROB: Treasure Hunt IV
 * ALGO: Math
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

long long lol(long long x)
{
    if (x < 0) return 0;
    long long r = sqrt(x) / 2;
    long long res = 0;
    res = min(x - 4 * r * r + 1, 4 * r + 1);
    if (r) {
        r--;
        res += (1 + 4 * r + 1) * (r + 1) / 2;
    }
    return res;
}

int main()
{
    long long a, b;
    while (~scanf("%lld%lld", &a, &b)) {
        long long ans = lol(b) - lol(a - 1);
        printf("%lld\n", ans);
    }

    return 0;
}
