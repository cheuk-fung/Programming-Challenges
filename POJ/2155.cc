/*
 *  SRC: POJ 2155
 * PROB: Matrix
 * ALGO: BIT
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int maxX, maxY;
bool bit[1024][1024];

inline int lowbit(int x)
{
    return x & -x;
}

void BITUpdate(int x, int y, int val)
{
    for (int i = x; i <= maxX; i += lowbit(i))
        for (int j = y; j <= maxY; j +=lowbit(j))
            bit[i][j] ^= val;
}

bool BITSum(int x, int y)
{
    long long res = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            res ^= bit[i][j];
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(bit, 0, sizeof(bit));

        int n, o;
        scanf("%d%d", &n, &o);
        maxX = maxY = n;

        while (o--) {
            char ctrl[10];
            scanf("%s", ctrl);
            if (ctrl[0] == 'C') {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                BITUpdate(x1, y1, 1);
                BITUpdate(x1, y2 + 1, 1);
                BITUpdate(x2 + 1, y1, 1);
                BITUpdate(x2 + 1, y2 + 1, 1);
            }
            else {
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%d\n", BITSum(x, y));
            }
        }
        
        putchar(10);
    }

    return 0;
}
