/*
 *  SRC: POJ 2352
 * PROB: Stars
 * ALGO: BIT
 * DATE: Jul 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

const int maxX = 320010;
int bit[maxX];

// x must *not* be *zero*
inline int lowbit(int x)
{
    return x & -x;
}

int BITSum(int x)
{
    int res = 0;
    while (x > 0) {
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

void BITUpdate(int x, int val)
{
    while (x <= maxX) {
        bit[x] += val;
        x += lowbit(x);
    }
}

struct Point {
    int x, y;

    bool operator < (const Point& other) const
    {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
} star[15010];

int n;
int level[15010];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d%d", &star[i].x, &star[i].y);

    sort(star, star + n);

    for (int i = 0; i < n; i++) {
        BITUpdate(star[i].y + 1, 1);
        level[BITSum(star[i].y + 1) - 1]++;
    }


    for (int i = 0; i < n; i++)
        printf("%d\n", level[i]);

    return 0;
}

