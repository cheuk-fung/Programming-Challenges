/*
 *  SRC: POJ 2828
 * PROB: Buy Tickets
 * ALGO: BIT
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, bitMask;
int bit[200001], ans[200001];

struct Node {
    int p, v;
} peo[200001];

inline int lowbit(int x)
{
    return x & -x;
}

int sum(int x)
{
    int res = 0;
    while (x > 0) {
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

void update(int x)
{
    while (x <= n) {
        bit[x]--;
        x += lowbit(x);
    }
}

int findPos(int tot)
{
    int res = 0, cnt = 0, bM = bitMask;
    while (bM != 0) {
        if (res + bM < n && cnt + bit[res + bM] < tot) {
            res += bM;
            cnt += bit[res];
        }
        bM >>= 1;
    }

    return res + 1;
}

int countBit(int x)
{
    int res = 0;
    while (x) {
        x >>= 1;
        res++;
    }

    return res;
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        bitMask = 1 << (countBit(n) - 1);

        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &peo[i].p, &peo[i].v);
            bit[i] = lowbit(i);
        }

        for (int i = n; i >= 1; i--) {
            int pos = findPos(peo[i].p + 1);
            ans[pos] = peo[i].v;
            update(pos);
        }

        for (int i = 1; i < n; i++)
            printf("%d ", ans[i]);
        printf("%d\n", ans[n]);
    }


    return 0;
}
