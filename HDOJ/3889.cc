/*
 *  SRC: HDOJ 3889
 * PROB: Statistical Problems
 * ALGO: NULL
 * DATE: Jun 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

inline double sqr(double x) { return x * x; }

double x[10010];
double y[10010];

void z_scores(int n)
{
    double mx = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", x + i);
        mx += x[i];
    }
    mx /= n;

    double sd = 0;
    for (int i = 0; i < n; i++) {
        sd += sqr(x[i] - mx);
    }
    sd = sqrt(sd / n);

    printf("%.2lf", (x[0] - mx) / sd);
    for (int i = 1; i < n; i++) {
        printf(" %.2lf", (x[i] - mx) / sd);
    }
    printf("\n");
}

void t_tests(int n)
{
    double mp, ms = 0;
    scanf("%lf", &mp);
    for (int i = 0; i < n; i++) {
        scanf("%lf", x + i);
        ms += x[i];
    }
    ms /= n;

    double sd = 0;
    for (int i = 0; i < n; i++) {
        sd += sqr(x[i] - ms);
    }
    sd = sqrt(sd / (n - 1));
    double se = sd / sqrt(n);

    printf("%.2lf\n", (ms - mp) / se);
}

void correlation_and_regression(int n, int p)
{
    double mx = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", x + i);
        mx += x[i];
    }
    mx /= n;

    double sdx = 0;
    for (int i = 0; i < n; i++) {
        sdx += sqr(x[i] - mx);
    }
    sdx = sqrt(sdx / n);

    double my = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", y + i);
        my += y[i];
    }
    my /= n;

    double sdy = 0;
    for (int i = 0; i < n; i++) {
        sdy += sqr(y[i] - my);
    }
    sdy = sqrt(sdy / n);

    double r = 0;
    for (int i = 0; i < n; i++) {
        r += (x[i] - mx) * (y[i] - my);
    }
    r /= n * sdx * sdy;

    if (p == 3) {
        printf("%.2lf\n", r);
    } else {
        double b = r * sdy / sdx;
        double a = my - b * mx;
        printf("%.2lf %.2lf\n", a, b);
    }
}

int main()
{
    int n, p;
    while (~scanf("%d%d", &p, &n)) {
        switch (p) {
            case 1: z_scores(n); break;
            case 2: t_tests(n); break;
            default: correlation_and_regression(n, p);
        }
    }

    return 0;
}

