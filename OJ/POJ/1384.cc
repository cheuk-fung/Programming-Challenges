/*
 *  SRC: POJ 1384
 * PROB: Piggy-Bank
 * ALGO: DP
 * DATE: Jul 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

long long f[10001];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(f, 0x3f, sizeof(f));

        int empty, full, n;
        scanf("%d%d%d", &empty, &full, &n);

        int m = full - empty;
        f[0] = 0;
        for (int i = 0; i < n; i++) {
            int v, w;
            scanf("%d%d", &v, &w);

            for (int j = w; j <= m; j++) {
                f[j] = min(f[j], f[j - w] + v);
            }
        }

        if (f[m] < INF) {
            printf("The minimum amount of money in the piggy-bank is %lld.\n", f[m]);
        } else {
            puts("This is impossible.");
        }
    }

    return 0;
}

