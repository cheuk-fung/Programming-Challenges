/*
 *  SRC: POJ 1017
 * PROB: Packets
 * ALGO: NULL
 * DATE: Nov 27, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

int solve()
{
    int a, b, c, d, e, f;
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    if (!(a || b || c || d || e || f)) return 0;

    int ans = f + e + d + (c + 3) / 4;
    int used = f * 36 + e * 25 + d * 16 + c * 9 + b * 4;

    int cb[4] = {0, 5, 3, 1};
    b -= d * 5 + cb[c % 4];
    if (b > 0) ans += (b + 8) / 9;

    a -= ans * 36 - used;
    if (a > 0) ans += (a + 35) / 36;

    printf("%d\n", ans);

    return 1;
}

int main()
{
    while (solve()) ;

    return 0;
}

