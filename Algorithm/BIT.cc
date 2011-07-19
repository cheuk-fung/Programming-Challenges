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

int BITSum(int x, int y)
{
    int res = 0;
    while (x > 0) {
        int ty = y;
        while (ty > 0) {
            res += bit[x][ty];
            ty -= lowbit(ty);
        }
//        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

void BITUpdate(int x, int y, int val)
{
    while (x <= maxX) {
        int ty = y;
        while (ty <= maxY) {
            bit[x][ty] += val;
            ty += lowbit(ty);
        }
//        bit[x] += val;
        x += lowbit(x);
    }
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
