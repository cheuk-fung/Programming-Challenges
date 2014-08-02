/*
 *  SRC: ZOJ 3488
 * PROB: Conic Section
 * ALGO: NULL
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>

const double eps = 1e-12;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        double a, b, c, d, e, f;
        scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f);
        if (fabs(a - c) < eps) puts("circle");
        else if (a * c > eps) puts("ellipse");
        else if (fabs(a) < eps || fabs(c) < eps) puts("parabola");
        else puts("hyperbola");
    }

    return 0;
}

