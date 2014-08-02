/*
 *  SRC: HDOJ 4254
 * PROB: A Famous Game
 * ALGO: Math
 * DATE: Jul 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int task = 1;
    int n, p, q;
    while (~scanf("%d%d%d", &n, &p, &q)) {
        double ans = 0, numerator = 1;
        for (int i = 1; i <= n - p; i++) {
            numerator *= 1.0 * (q + i) / i * (n - p - i + 1) / (n - q - i + 1);
            ans += numerator * i / (n - p);
            ans /= 1 + numerator;
            numerator /= 1 + numerator;
        }
        printf("Case %d: %.4lf\n", task++, ans);
    }

    return 0;
}

