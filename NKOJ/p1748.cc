/*
 *  SRC: NKOJ p1748
 * PROB: Black and white painting
 * ALGO: Math
 * DATE: May 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int calc(int n, int m)
{
    if (n < 8 || m < 8) return 0;

    int a = (n - 8) / 2 + 1;
    int b = (m - 8) / 2 + 1;
    int c = 0, d = 0;
    if (n > 8 && m > 8) {
        c = (n - 9) / 2 + 1;
        d = (m - 9) / 2 + 1;
    }

    return a * b + c * d;
}

bool work()
{
    int n, m, c;
    scanf("%d%d%d", &n, &m, &c);
    if (n == 0 && m == 0 && c == 0) return false;

    if (c) printf("%d\n", calc(n, m));
    else printf("%d\n", calc(n - 1, m) + (calc(8, m - 1)));

    return true;
}

int main()
{
    while (work()) ;

    return 0;
}


