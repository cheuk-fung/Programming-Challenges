/*
 *  SRC: NKOJ
 * TASK: Gauss is a genius
 * ALGO: Math
 * DATE: 04/09/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>

void work()
{
    long long L, R;
    scanf("%lld%lld", &L, &R);
    long long ans = (L + R) * (R - L + 1) / 2;
    printf("%d\n", int(ans % 10));
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) work();

    return 0;
}

