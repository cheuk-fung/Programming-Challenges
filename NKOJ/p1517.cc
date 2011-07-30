/*
 *  SRC: NKOJ p1517
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

void ZeroOnePack(int value, int TotalValue, int task)
{
    for (int i = TotalValue; i >= value; i--)
	if (f[i - value] == task) f[i] = task;
}

void CompletePack(int value, int TotalValue, int task)
{
    for (int i = value; i <= TotalValue; i++)
	if (f[i - value] == task) f[i] = task;
}

void MultiplePack(int value, int amount, int TotalValue, int task)
{
    if (value * amount >= TotalValue)
	CompletePack(value, TotalValue, task);
    else {
	for (int k = 1; k < amount; amount -= k, k <<= 1)
	    ZeroOnePack(k * value, TotalValue, task);

	ZeroOnePack(value * amount, TotalValue, task);
    }
}

int main()
{
    double ta;
    int a, b, c, d, e;
    for (int task = 1; scanf("%lf%d%d%d%d", &ta, &b, &c, &d, &e) == 5; task++) {
        a = (ta + eps) * 100;
        f[0] = task;
        MultiplePack(25, b, a, task);
        MultiplePack(10, c, a, task);
        MultiplePack( 5, d, a, task);
        MultiplePack( 1, e, a, task);
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

