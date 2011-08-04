/*
 *  SRC: NKOJ p1200
 * PROB: Euclid's Game 
 * ALGO: Number Theory
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

bool gcd(int a, int b)
{
    if (b == 0) return false;
    if (a / b >= 2) return true;
    return !gcd(b, a % b);
}

bool solve()
{
    int a, b;
    scanf("%d%d", &a, &b);
    if (!(a | b)) return false;

    if (a < b) {
        int t = a;
        a = b;
        b = t;
    }

    if (gcd(a, b)) puts("Stan wins");
    else puts("Ollie wins");

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}
