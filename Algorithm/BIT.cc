/*
 *  SRC: POJ 1195
 * PROB: Mobile phones
 * ALGO: 2D BIT(Binary Indexed Tree)
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int maxX, maxY;
int bit[1025][1025];
// int bitMask
int n;

// x must *not* be *zero*
inline int lowbit(int x)
{
    return x & -x;
}

void BITUpdate(int x, int y, int val)
{
    for (int i = x; i <= maxX; i += lowbit(i))
        for (int j = y; j <= maxY; j +=lowbit(j))
            bit[i][j] += val;
}

long long BITSum(int x, int y)
{
    long long res = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            res += bit[i][j];
    return res;
}

// bitMask = countBit(maxX);
// not used in this program
int BITFind(int tot)
{
    int res = 0, cnt = 0, bM = bitMask;
    while (bM != 0) {
        if (res + bM < n && cnt + bit[res + bM] < tot) { // find the left one
     // if (res + bM <=n && cnt + bit[res + bM] <=tot) { // find the right one
            res += bM;
            cnt += bit[res];
        }
        bM >>= 1;
    }

    return res + 1; // left
 // return res;     // right
}

// not used in this program
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
    int ins;
    scanf("%d", &ins);
    scanf("%d", &n);
    maxX = maxY = n;

    while (scanf("%d", &ins) != EOF && ins != 3) {
        if (ins == 1) {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            BITUpdate(x + 1, y + 1, a);
        }
        else {
            int l, b, r, t;
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", BITSum(r + 1, t + 1) - BITSum(l, t + 1) - BITSum(r + 1, b) + BITSum(l, b));
        }
    }

    return 0;
}
