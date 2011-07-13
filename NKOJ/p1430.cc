/*
 *  SRC: NKOJ p1430
 * PROB: Fibonacci
 * ALGO: Number Theory
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

struct Fib {
    int a, b, c, d;

    Fib(int aa, int bb, int cc, int dd)
        : a(aa), b(bb), c(cc), d(dd)
    { }

    Fib& operator *= (Fib& other)
    {
        Fib r(1, 0, 0, 1);
        r.a = (a * other.a + b * other.c) % 10000;
        r.b = (a * other.b + b * other.d) % 10000;
        r.c = (c * other.a + d * other.c) % 10000;
        r.d = (c * other.b + d * other.d) % 10000;

        *this = r;

        return *this;
    }
};

bool solve()
{
    int n;
    scanf("%d", &n);

    if (n == -1) return false;

    if (n == 0) {
        puts("0");
        return true;
    }

    Fib f(1, 1, 1, 0), r(1, 0, 0, 1);

    while (n) {
        if (n & 1) r *= f;
        n >>= 1;
        f *= f;
    }

    // printf("%d %d %d %d\n", r.a, r.b, r.c, r.d);
    printf("%d\n", r.c);


    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}
