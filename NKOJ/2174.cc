/*
 *  SRC: NKOJ 2174
 * PROB: Hill Driving
 * ALGO: Bisection
 * DATE: Aug 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::min;

const double eps = 1e-13;

double a, b, vmax, f;
int r;

struct Segment {
    double x, y, s, len, v;
} road[10000];

bool check(double v, double f_curr, double* time)
{
    *time = 0;
    for (int i = 0; i < r; i++) {
        double c = a * v + b * road[i].s;
        if (c <= 0) *time += road[i].len / road[i].v;
        else {
            *time += road[i].len / v;
            if ((f_curr -= c * road[i].len) < 0) return 0;
        }
    }

    return 1;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%lf%lf%lf%lf%d", &a, &b, &vmax, &f, &r);
        f *= 1000;

        for (int i = 0; i < r; i++) {
            scanf("%lf%lf", &road[i].x, &road[i].y);
            road[i].s = road[i].y / road[i].x;
            road[i].len = hypot(road[i].x, road[i].y);
            road[i].v = min(-b * road[i].s / a, vmax);
        }

        double left = 0, right = vmax, time = 1e12, time_curr;
        while (left + eps < right) {
            double mid = (left + right) / 2;
            if (check(mid, f, &time_curr)) {
                left = mid;
                time = time_curr;
            }
            else right = mid;
        }

        time < 1e12 ?  printf("%.10f\n", time / 1000) : puts("IMPOSSIBLE");
    }

    return 0;
}
