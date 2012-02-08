/*
 *  SRC: HDOJ 3233
 * PROB: Download Manager
 * ALGO: NULL
 * DATE: Feb 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int tasks = 0;
    int T, n, B;
    while (scanf("%d%d%d", &T, &n, &B), T || n || B) {
        double ans = 0.0;
        for (int i = 0; i < T; i++) {
            double s;
            int p;
            scanf("%lf%d", &s, &p);
            ans += s * (100 - p);
        }
        printf("Case %d: %.2f\n\n", ++tasks, ans / B / 100);
    }

    return 0;
}

