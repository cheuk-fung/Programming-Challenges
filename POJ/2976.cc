/*
 *  SRC: POJ 2976
 * PROB: Dropping tests
 * ALGO: 0-1 Fractional Programming
 * DATE: Jul 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const double eps = 1e-6;

int n, k;
int a[MAXN], b[MAXN];
double c[MAXN];

inline bool ls(double x, double y) { return x + eps < y; }

bool check(double x)
{
    for (int i = 0; i < n; i++) c[i] = a[i] - x * b[i];
    sort(c, c + n, ls);

    double tot = 0;
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (ls(tot + c[i], 0)) break;
        tot += c[i];
        cnt++;
    }

    return cnt >= k;
}

int main()
{
    while (scanf("%d%d", &n, &k), n || k) {
        k = n - k;
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < n; i++) scanf("%d", b + i);

        double l = 0, r = 1;
        for (int times = 0; times < 20 && ls(l, r); times++) {
            double mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }

        printf("%.0f\n", l * 100);
    }

    return 0;
}

