/*
 *  SRC: HDOJ ACM Steps
 * PROB: Higher Math
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

inline bool check()
{
    long long a, b, c;
    scanf("%I64d%I64d%I64d", &a, &b, &c);
    if (a * a + b * b - c * c == 0) return 1;
    if (a * a + c * c - b * b == 0) return 1;
    if (b * b + c * c - a * a == 0) return 1;
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("Scenario #%d:\n", i);
        if (check()) printf("yes\n\n");
        else printf("no\n\n");
    }

    return 0;
}
