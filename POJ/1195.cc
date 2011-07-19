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
int n;

// x must *not* be *zero*
inline int lowbit(int x)
{
    return x & -x;
}

int sum(int x, int y)
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

void update(int x, int y, int val)
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
            update(x + 1, y + 1, a);
        }
        else {
            int l, b, r, t;
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", sum(r + 1, t + 1) - sum(l, t + 1) - sum(r + 1, b) + sum(l, b));
        }
    }

    return 0;
}
