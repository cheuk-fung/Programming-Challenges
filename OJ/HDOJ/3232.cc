/*
 *  SRC: HDOJ 3232
 * PROB: Crossing Rivers
 * ALGO: NULL
 * DATE: Feb 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int tasks = 1;

    int n, D;
    while (scanf("%d%d", &n, &D), n || D) {
        double ans = 0;
        int river_sum = 0;
        for (int i = 0; i < n; i++) {
            int L, v;
            scanf("%*d%d%d", &L, &v);
            ans += L * 2.0 / v;
            river_sum += L;
        }
        ans += D - river_sum;

        printf("Case %d: %.3f\n\n", tasks++, ans);
    }

    return 0;
}

