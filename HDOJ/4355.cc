/*
 *  SRC: HDOJ 4355
 * PROB: Party All the Time
 * ALGO: trisection
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

const int MAXN = 50010;

double x[MAXN], w[MAXN];

double calc(double x0, int n)
{
    double res = 0;
    for (int i = 0; i < n; i++) {
        double s = fabs(x[i] - x0);
        res += s * s * s * w[i];
    }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", x + i, w + i);
        }

        double l = x[0], r = x[n - 1];
        while (l + 1e-6 < r) {
            double m1 = (l + r) / 2;
            double m2 = (m1 + r) / 2;
            double ans1 = calc(m1, n);
            double ans2 = calc(m2, n);
            if (ans1 <= ans2) r = m2;
            else l = m1;
        }
        printf("Case #%d: %.0f\n", task, calc(l, n));
    }

    return 0;
}

