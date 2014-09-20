#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

template<class T> inline T sqr(T x) { return x * x; }

int main()
{
    int x1, y1, r1, x2, y2, r2;
    while (~scanf("%d%d%d%d%d%d", &x1, &y1, &r1, &x2, &y2, &r2)) {
        double dist = sqrt((double)sqr(x1 - x2) + (double)sqr(y1 - y2));
        double ans = 0;
        if (dist >= (r1 + r2)) {
            ans = (dist - (r1 + r2)) / 2.0;
        } else if (dist + min(r1, r2) <= max(r1, r2)) {
            ans = (max(r1, r2) - (dist + min(r1, r2))) / 2.0;
        }
        printf("%.10f\n", ans);
    }

    return 0;
}

