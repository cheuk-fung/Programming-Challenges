/*
 *  SRC: POJ 2581
 * PROB: Exact Change Only
 * ALGO: DP(Multiple Pack)
 * DATE: Jul 28, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const double eps = 1e-12;

int f[510];

void zero_one_pack(int value, int max_value, int task)
{
    for (int i = max_value; i >= value; i--)
        if (f[i - value] == task) f[i] = task;
}

void complete_pack(int value, int max_value, int task)
{
    for (int i = value; i <= max_value; i++)
        if (f[i - value] == task) f[i] = task;
}

void multiple_pack(int value, int amount, int max_value, int task)
{
    if (value * amount >= max_value)
        complete_pack(value, max_value, task);
    else {
        for (int k = 1; k < amount; amount -= k, k <<= 1)
            zero_one_pack(k * value, max_value, task);

        zero_one_pack(value * amount, max_value, task);
    }
}

int main()
{
    double ta;
    int a, b, c, d, e;
    for (int task = 1; scanf("%lf%d%d%d%d", &ta, &b, &c, &d, &e) == 5; task++) {
        a = (ta + eps) * 100;
        f[0] = task;
        multiple_pack(25, b, a, task);
        multiple_pack(10, c, a, task);
        multiple_pack( 5, d, a, task);
        multiple_pack( 1, e, a, task);
        if (f[a] != task) puts("NO EXACT CHANGE");
        else {
            int B = 0, C = 0, D = 0, E = 0, now = a;
            while (now && B < b && f[now - 25] == task) { B++; now -= 25; }
            while (now && C < c && f[now - 10] == task) { C++; now -= 10; }
            while (now && D < d && f[now -  5] == task) { D++; now -=  5; }
            while (now && E < e && f[now -  1] == task) { E++; now -=  1; }
            printf("%d %d %d %d\n", B, C, D, E);
        }
    }

    return 0;
}
