/*
 *  SRC: POJ 2586
 * PROB: Y2K Accounting Bug
 * ALGO: Greedy
 * DATE: Jul 18, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int s, d, rest;
    while (scanf("%d%d", &s, &d) != EOF) {
        if (4 * s < d) rest = 10 * s - 2 * d;
        else if (3 * s < 2 * d) rest = 8 * s - 4 * d;
        else if (2 * s < 3 * d) rest = 6 * s - 6 * d;
        else if (s < 4 * d) rest = 3 * s - 9 * d;
        else rest = -12 * d;

        if (rest >= 0) printf("%d\n", rest);
        else puts("Deficit");
    }

    return 0;
}
