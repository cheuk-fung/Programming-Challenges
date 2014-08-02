/*
 *  SRC: POJ 3122
 * PROB: Pie
 * ALGO: Bisection
 * DATE: Jul 18, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;

const double INF = 1e10;
const double eps = 1e-8;
const double pi = acos(-1.0);
int n, f, pie[10010];
double vol[10010];

int check(double v)
{
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (vol[i] + eps < v) break;
        cnt += vol[i] / v;
    }

    if (cnt >= f + 1) return 1;
    else return 0;
}

double bisection()
{
    double low = 0, high = INF;
    while (low + eps < high) {
        double mid = (low + high + 1e-5) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1e-5;
    }

    return low;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &f);
        for (int i = 0 ; i < n; i++) {
            scanf("%d", pie + i);
        }

        sort(pie, pie + n);
        for (int i = 0; i < n; i++)
            vol[i] = pi * pie[i] * pie[i];

        printf("%.5f\n", bisection());
    }

    return 0;
}
