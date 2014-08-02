/*
 *  SRC: HDOJ 3859
 * PROB: Inverting Cups
 * ALGO: Math
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

unsigned long long check(unsigned long long a, unsigned long long b)
{
    if (a % b == 0) return a / b;
    if ((a & 1) && !(b & 1)) return 0;

    if (a > 2 * b) {
        if ((b - a % b) & 1) return a / b + 2;
        else return a / b + 1;
    } else {
        if ((a & 1) && (b & 1)) return 3;
        if (!(a & 1) && !(b & 1)) return 3;
        return check(a, a - b);
    }
}

int main()
{
    unsigned long long a, b;
    while (~scanf("%I64u%I64u", &a, &b)) {
        unsigned long long r = check(a, b);
        if (r == 0) {
            puts("No Solution!");
        } else {
            printf("%I64u\n", r);
        }
    }

    return 0;
}

