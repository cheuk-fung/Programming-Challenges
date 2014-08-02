/*
 *  SRC: HDOJ 4336
 * PROB: Card Collector
 * ALGO: Probability theory
 * DATE: Aug 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXN = 20;

double p[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%lf", p + i);
        }

        double ans = 0;
        for (int bit = 1, final = 1 << n; bit < final; bit++) {
            int cnt = 0;
            double probability = 0;
            for (int i = 0; i < n; i++) {
                if ((bit >> i) & 1) {
                    cnt++;
                    probability += p[i];
                }
            }
            if (cnt & 1) {
                ans += 1 / probability;
            } else {
                ans -= 1 / probability;
            }
        }

        printf("%.5f\n", ans);
    }

    return 0;
}

