/*
 *  SRC: ZOJ 3551
 * PROB: Bloodsucker
 * ALGO: Math
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        double p;
        scanf("%d%lf", &n, &p);
        long long m = (long long)n * (n - 1) / 2;
        double r = 0;
        for (int i = 1; i < n; i++) {
            r += m / (p * i * (n - i));
        }
        printf("%.3f\n", r);
    }

    return 0;
}

