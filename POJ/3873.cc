/*
 *  SRC: POJ 3873
 * PROB: Trick or Treat
 * ALGO: Bisection
 * DATE: Aug 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

const double eps = 1e-12, inf = 1e300;

struct Point {
    double x, y;
};

int n;
Point p[50000];

bool check(double d, double& x1, double& x2)
{
    double t_x1 = -inf, t_x2 = inf;
    for (int i = 0; i < n; i++) {
        if (d < fabs(p[i].y)) return false;
        double x_eps = sqrt(d * d - p[i].y * p[i].y),
               a = p[i].x - x_eps,
               b = p[i].x + x_eps;
        if (a > t_x1) t_x1 = a;
        if (b < t_x2) t_x2 = b;
        if (t_x1 > t_x2) return false;
    }
    x1 = t_x1;
    x2 = t_x2;
    return true;
}

int main()
{
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);

        double x1, x2, left = -1e12, right = 1e12, cnt = 0;
        while (right - left > eps && cnt++ < 100) {
            double mid = (left + right) / 2.0;
            if (check(mid, x1, x2)) right = mid;
            else left = mid;
        }

        printf("%.9f %.9f\n", (x1 + x2) / 2.0, left + eps);
    }

    return 0;
}

