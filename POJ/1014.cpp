/*
 *  SRC: POJ
 * TASK: Dividing
 * ALGO: DP(Multiple Pack)
 * DATE: Nov. 27, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

const int MaxN = 60000;
int f[MaxN + 1];

void CompletePack(int value, int TotalValue, int task)
{
    for (int i = value; i <= TotalValue; i++)
	if (f[i - value] == task) f[i] = task;
}

void ZeroOnePack(int value, int TotalValue, int task)
{
    for (int i = TotalValue; i >= value; i--)
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
    for (int task = 1; ; task++) {
	int n[6], TotalValue = 0;
	for (int i = 0; i < 6; i++) {
	    scanf("%d", &n[i]);
	    TotalValue += n[i] * (i + 1);
	}
	if (!TotalValue) break;

	printf("Collection #%d:\n", task);
	if (TotalValue % 2) {
	    printf("Can't be divided.\n\n");
	    continue;
	}

	f[0] = task;
	for (int i = 0; i < 6; i++)
	    MultiplePack(i + 1, n[i], TotalValue / 2, task);

	if (f[TotalValue / 2] == task) printf("Can be divided.\n\n");
	else printf("Can't be divided.\n\n");
    }

    return 0;
}

