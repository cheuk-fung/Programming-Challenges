/*
 *  SRC: HDOJ 4349
 * PROB: Xiao Ming's Hope
 * ALGO: NULL
 * DATE: Aug 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int calc(int n)
{
    int bit = 31;
    while ((n >> bit) == 0) bit--;
    if (n == 1 << bit) return 2;
    return calc(n ^ (1 << bit)) << 1;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        printf("%d\n", calc(n));
    }

    return 0;
}
