/*
 *  SRC: NKOJ p1249
 * PROB: 分解素因子
 * ALGO: Prime
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAXN = 1 << 16;
int p[10000];
bool b[MAXN];

int prime()
{
    int sum = 0;
    memset(b, true, sizeof(b));
    b[0] = b[1] = false;
    for (int i = 0; i < MAXN; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] <= MAXN; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return sum;
}

int main()
{
    int sum = prime();

    int k;
    scanf("%d", &k);

    while (k--) {
        int x;
        scanf("%d", &x);

        bool flag = false;
        for (int i = 0; x > 1 && i < sum; i++) {
            while (x % p[i] == 0) {
                if (flag) putchar('*');
                else flag = true;
                printf("%d", p[i]);

                x /= p[i];
            }
        }

        putchar(10);
    }

    return 0;
}

