/*
 *  SRC: HDOJ ACM Steps
 * PROB: Just A Triangle
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int a, b, c;

inline bool check_right()
{
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
        scanf("%d%d%d", &a, &b, &c);
        if (a == b || a == c || b == c) puts("perfect");
        else if (check_right()) puts("good");
        else puts("just a triangle");
    }

    return 0;
}
