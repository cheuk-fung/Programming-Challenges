/*
 *  SRC: HDOJ 4024
 * PROB: Dwarven Sniper’s hunting
 * ALGO: Bisection
 * DATE: Sep 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

const double eps = 1e-8;

struct Point {
    double x, y;
} L, D, vL;

double vD, vB, R;
double t;

inline double sqr(double x) { return x * x; }

bool check(double T)
{
    double S = fabs(sqrt(sqr(D.x - (L.x + vL.x * T)) + \
                         sqr(D.y - (L.y + vL.y * T))) - R);
    if (S / vD <= T - t) return true;
    return false;
}

int main()
{
    while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", \
                &L.x, &L.y, &D.x, &D.y, &vL.x, &vL.y, &vD, &vB, &R), \
            L.x != 0 || L.y != 0 || D.x != 0 || D.y != 0 || vL.x != 0 || \
            vL.y != 0 || vD != 0 || vB != 0 || R != 0) {
        t = 1.0 * R / vB;
        double l = t + eps, r = 1e9;
        for (int i = 0; i < 100 && l < r; i++) {
            double mid = (l + r) / 2.;
            if (check(mid)) r = mid;
            else l = mid + eps;
        }

        printf("%.3f %.3f\n", R, l);
    }

    return 0;
}
