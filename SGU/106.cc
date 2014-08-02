#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

long long extended_euclid(long long a, long long b, long long *x, long long *y)
{
    if (!b) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long r = extended_euclid(b, a % b, x, y);
    long long t = *x;
    *x = *y;
    *y = t - a / b * *y;

    return r;
}

int main(int argc, char *argv[])
{
    long long a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    // scanf("%lld%lld%lld%lld%lld%lld%lld", &a, &b, &c, &x1, &x2, &y1, &y2);
    // ax + by = -c;
    c *= -1;

    long long ans = 0;
    if (a == 0 && b == 0) {
        if (c == 0) {
            ans = (x2 - x1 + 1) * (y2 - y1 + 1);
        } else {
            ans = 0;
        }
    } else if (a == 0) {
        long long r = c / b;
        if (c % b == 0 && y1 <= r && r <= y2) {
            ans = x2 - x1 + 1;
        } else {
            ans = 0;
        }
    } else if (b == 0) {
        long long r = c / a;
        if (c % a == 0 && x1 <= r && r <= x2) {
            ans = y2 - y1 + 1;
        } else {
            ans = 0;
        }
    } else {
        long long x0, y0;
        long long g = extended_euclid(llabs(a), llabs(b), &x0, &y0);
        if (llabs(c) % g) {
            ans = 0;
        } else {
            x0 *= c / g;
            y0 *= c / g;
            if (a < 0) x0 *= -1;
            if (b < 0) y0 *= -1;

            long long delta_x = b / g;
            long long delta_y = -1 * a / g;

            // x1 <= x = x0 + k * delta_x <= x2
            long long xkmin, xkmax;
            if (delta_x > 0) {
                xkmin = ceil(1.0 * (x1 - x0) / delta_x);
                xkmax = floor(1.0 * (x2 - x0) / delta_x);
            } else {
                xkmin = ceil(1.0 * (x2 - x0) / delta_x);
                xkmax = floor(1.0 * (x1 - x0) / delta_x);
            }

            // y1 <= y = y0 + k * delta_y <= y2
            long long ykmin, ykmax;
            if (delta_y > 0) {
                ykmin = ceil(1.0 * (y1 - y0) / delta_y);
                ykmax = floor(1.0 * (y2 - y0) / delta_y);
            } else {
                ykmin = ceil(1.0 * (y2 - y0) / delta_y);
                ykmax = floor(1.0 * (y1 - y0) / delta_y);
            }

            ans = min(xkmax, ykmax) - max(xkmin, ykmin) + 1;
            if (ans < 0) ans = 0;
        }
    }
    // printf("%lld\n", ans);
    cout << ans << endl;

    return 0;
}
