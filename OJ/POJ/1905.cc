/*
 *  SRC: POJ 1905
 * PROB: Expanding Rods
 * ALGO: Bisection
 * DATE: Jul 18, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

const double eps = 1e-12;
const double pi = acos(-1);
long long l0, n;
double c, L;

int check(double p)
{
    double t = 2.0 * L / p * sin(p / 2.0);
    return t - eps <= l0;
}

int main()
{
    while (scanf("%lld%lld%lf", &l0, &n, &c) != EOF) {
        if (l0 < 0 && n < 0 && c < eps) break;

        if (l0 == 0 || n == 0 || c < eps) {
            puts("0.000");
            continue;
        }

        L = (1.0 + n * c) * l0;

        double low = 0.0, high = pi;
        while (low + eps < high) {
            double mid = (low + high - eps) / 2.0;
            if (check(mid)) high = mid;
            else low = mid + eps;
        }

        double r = L / low;
        printf("%.3f\n", r - sqrt(r * r - (l0 * l0) / 4.0));
    }

    return 0;
}
