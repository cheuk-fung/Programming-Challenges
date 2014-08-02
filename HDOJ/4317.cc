/*
 *  SRC: HDOJ 4317
 * PROB: Unfair Nim
 * ALGO: Gambling
 * DATE: Jul 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int stone[11];
int f[2][1 << 10];

inline int count_one(int x)
{
    x = (x & 0x55555555) + ((x >>  1) & 0x55555555);
    x = (x & 0x33333333) + ((x >>  2) & 0x33333333);
    x = (x & 0x0f0f0f0f) + ((x >>  4) & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + ((x >>  8) & 0x00ff00ff);
    x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
    return x;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &stone[i]);
        }

        memset(f, 0x3f, sizeof f);
        f[0][0] = 0;
        for (int i = 1; i <= 21; i++) {
            int b = 0;
            for (int j = 0; j < n; j++) {
                b |= (stone[j] >> (i - 1) & 1) << j;
            }
            memset(f[i & 1], 0x3f, sizeof f[i & 1]);
            for (int j = 0, final = 1 << n; j < final; j++) {
                if (f[(i - 1) & 1][j] == INF) continue;
                for (int k = 0; k < final; k++) {
                    if (count_one(b ^ j ^ k) & 1) continue;
                    int mask = (b & j) | (b & k) | (j & k);
                    int tot = (1 << (i - 1)) * count_one(k);
                    f[i & 1][mask] = min(f[i & 1][mask], f[(i - 1) & 1][j] + tot);
                }
            }
        }

        if (f[1][0] == INF) puts("impossible");
        else printf("%d\n", f[1][0]);
    }

    return 0;
}

