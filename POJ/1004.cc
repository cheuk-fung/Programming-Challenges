/*
 *  SRC: POJ
 * TASK: Financial Management
 * ALGO: NULL
 * DATE: 05/10/2011 
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

