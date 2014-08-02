/*
 *  SRC: POJ 1183
 * PROB: 反正切函数的应用
 * ALGO: Math
 * DATE: Jul 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

int main()
{
    long long a, b, c;

    scanf("%lld", &a);

    for (b = a + sqrt(a * a + 1); b > a; b--) {
        if ((a * b + 1) % (b - a) == 0) {
            c = (a * b + 1) / (b - a);
            break;
        }
    }

    printf("%lld\n", b + c);

    return 0;
}
