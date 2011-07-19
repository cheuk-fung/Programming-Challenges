/*
 *  SRC: NKOJ p1822
 * PROB: Goldbach's Conjecture
 * ALGO: NULL
 * DATE: Nov 27, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

const int MaxN = 1000000;
int prime[100000], sum, check[MaxN];

void getPrime()
{
    for (int i = 2; i < MaxN; i++)
	if (!check[i]) {
	    prime[sum++] = i;
	    for (int j = 2; j * i < MaxN; j++) check[j * i] = 1;
	}
}

int Goldbach()
{
    int n;
    scanf("%d", &n);
    if (!n) return 0;
    for (int i = 0; i < sum; i++)
	if (!check[n - prime[i]]) {
	    printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
	    break;
	}
    return 1;
}

int main()
{
    getPrime();
    while (Goldbach()) ;

    return 0;
}


