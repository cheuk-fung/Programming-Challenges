/*
 *  SRC: NKOJ p1641
 * PROB: Japan
 * ALGO: BIT
 * DATE: Jul 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

const int maxX = 1010;
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
        if (x == other.x) return y > other.y;
        return x > other.x;
    }
} city[1000010];

int T, n, m, k;

int main()
{
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        memset(bit, 0, sizeof(bit));

        scanf("%d%d%d", &n, &m, &k);

        for (int i = 0; i < k; i++)
            scanf("%d%d", &city[i].x, &city[i].y);

        sort(city, city + k);

        long long cnt = 0;
        for (int i = 0; i < k; i++) {
            cnt += BITSum(city[i].y);
            BITUpdate(city[i].y + 1, 1);
        }

        printf("Test case %d: %lld\n", cases, cnt);
    }

    return 0;
}


