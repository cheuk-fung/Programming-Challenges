#include <cassert>
#include <cstdio>
#include <algorithm>

using std::__gcd;

const int MAX_NUM = 2000000000;

int A[101], X[101];
long long g[101];

long long extended_euclidean(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long r = extended_euclidean(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

int main(int argc, char *argv[])
{
    int n, P, B;
    scanf("%d%d%d", &n, &P, &B);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
    }

    g[0] = P;
    for (int i = 1; i <= n; i++) {
        g[i] = __gcd((long long)A[i], g[i - 1]);
    }
    if (B % g[n] != 0) {
        puts("NO");
        return 0;
    }

    long long pre = B / g[n];
    for (int i = n; i > 0; i--) {
        long long x, y;
        long long d = extended_euclidean(A[i], g[i - 1], &x, &y);
        long long dx = g[i - 1] / d;
        long long dy = A[i] / d;
        x *= pre;
        y *= pre;

        long long k = -x / dx;
        if (x + k * dx < 0) k++;
        assert(x + k * dx >= 0);

        x += k * dx;
        y -= k * dy;

        if (x >= MAX_NUM) {
            puts("NO");
            return 0;
        }

        X[i] = x;
        pre = y;
    }

    puts("YES");
    for (int i = 1; i <= n; i++) {
        printf("%d%c", X[i], i == n ? '\n' : ' ');
    }

    return 0;
}


