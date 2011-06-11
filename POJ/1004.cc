/*
 *  SRC: POJ 1004
 * PROB: Financial Management
 * ALGO: NULL
 * DATE: May 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    float tot = 0;

    for (int i = 0; i < 12; i++) {
        float f;
        scanf("%f", &f);
        tot += f;
    }

    printf("$%.2f\n", tot / 12.0);

    return 0;
}

