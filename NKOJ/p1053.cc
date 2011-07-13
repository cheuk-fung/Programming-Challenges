/*
 *  SRC: NKOJ p1053
 * PROB: 哥德巴赫猜想
 * ALGO: Number Theory
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXN = (1 << 15) + 1;

int p[4000];
bool b[MAXN];

int getPrime()
{
    int sum = 0;
    b[0] = b[1] = false;
    for (int i = 2; i < MAXN; i++) b[i] = true;
    for (int i = 2; i < MAXN; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] < MAXN; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return sum;
}

int main()
{
    int sum = getPrime();

    while (1 + 1 == 2) {
        int n;
        scanf("%d", &n);
        if (!n) break;
        
        int cnt = 0;
        for (int i = 0; p[i] <= n / 2 && i < sum; i++)
            if (b[n - p[i]]) cnt++;

        printf("%d\n", cnt);
    }

    return 0;
}
