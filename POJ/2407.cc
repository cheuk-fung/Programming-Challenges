/*
 *  SRC: POJ 2407
 * PROB: Relatives
 * ALGO: Number Theory
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

int euler(int x)
{
    int r = x;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            r = r / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) r = r / x * (x - 1);

    return r;
}

int main()
{
    while (1 + 1 == 2) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;

        printf("%d\n", euler(n));
    }

    return 0;
}
