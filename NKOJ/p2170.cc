/*
 *  SRC: NKOJ
 * TASK: Happy ending
 * ALGO: Math
 * DATE: 04/09/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<cmath>

double pi;

double twodivide(double r, double v)
{
    double low = 0, high = r;
    while (high - low > -1e-10) {
        double mid = (low + high) / 2;
        double vt = pi * (r * mid * mid - 1.0 / 3.0 * mid * mid * mid);
        if (-1e-10 < vt - v && vt - v < 1e-10)
            return mid;
        if (vt - v < 1e-10) low = mid;
        else high = mid;
    }
}

void work()
{
    double r, v;
    scanf("%lf%lf", &r, &v);
    double Vball = 4.0 / 3.0 * pi * r * r * r;
    if (v - Vball > -1e-10 || (-1e-10 < v - Vball && v - Vball < 1e-10)) {
        printf("%.4f\n", 2.0 * r);
        return ;
    }
    double h;
    if (v - Vball / 2.0 < 1e-10) { //v < Vball / 2
        h = twodivide(r, v);
    }
    else {
        h = 2.0 * r - twodivide(r, Vball - v);
    }
    printf("%.4f\n", h);
}

int main()
{
    pi = acos(-1);

    int t;
    scanf("%d", &t);
    while (t--) work();

    return 0;
}

