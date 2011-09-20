/*
 *  SRC: NKOJ 1584
 * PROB: Joseph
 * ALGO: Math
 * DATE: Sep 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int ans[14];

int main()
{
    int k;
    for (int k = 1; k < 14; k++) {
        int m = k;
        while (++m) {
            int r = 2 * k;
            for (int p = 0; r > k; r--) {
                p = (p + m - 1) % r;
                if (p < k) break;
            }

            if (r == k) {
                ans[k] = m;
                break;
            }
        }
    }
    while (scanf("%d", &k), k) printf("%d\n", ans[k]);

    return 0;
}
