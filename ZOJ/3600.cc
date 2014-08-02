/*
 *  SRC: ZOJ 3600
 * PROB: Taxi Fare
 * ALGO: NULL
 * DATE: Apr 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int calc(double flag_down, double after3, double after10, double wait_fee, int wait_min, int d, int t)
{
    double res = flag_down;
    if (d > 10) {
        res += (d - 10) * after10;
        d = 10;
    }
    if (d > 3) {
        res += (d - 3) * after3;
    }
    res += (double)t / wait_min * wait_fee;

    return (int)(res + 0.5);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int d, t;
        scanf("%d%d", &d, &t);

        int orig_price = calc(10, 2, 3, 2, 5, d, t) + 1;
        int new_price  = calc(11, 2.5, 3.75, 2.5, 4, d, t);
        printf("%d\n", new_price - orig_price);
    }

    return 0;
}

