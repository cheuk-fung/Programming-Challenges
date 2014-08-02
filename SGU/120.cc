#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-12;

struct Point {
    double x, y;
} pnt[150];

int main(int argc, char *argv[])
{
    int n, n1, n2;
    scanf("%d%d%d", &n, &n1, &n2);
    n1 = (n - (n1 - 1)) % n;
    n2 = (n - (n2 - 1)) % n;
    scanf("%lf%lf", &pnt[n1].x, &pnt[n1].y);
    scanf("%lf%lf", &pnt[n2].x, &pnt[n2].y);

    Point a = pnt[n1], b = pnt[n2];
    if (n1 > n2) {
        swap(a, b);
    }

    double theta = 2 * pi / n * abs(n2 - n1);
    double c1 = b.x - a.x * cos(theta) + a.y * sin(theta);
    double c2 = b.y - a.x * sin(theta) - a.y * cos(theta);
    double x0 = (c1 * (1 - cos(theta)) - c2 * sin(theta)) / (2 - 2 * cos(theta));
    double y0 = (c1 * sin(theta) + c2 * (1 - cos(theta))) / (2 - 2 * cos(theta));

    theta = 2 * pi / n;
    for (int i = 1; i < n; i++) {
        double x = pnt[(n1 + i - 1) % n].x - x0;
        double y = pnt[(n1 + i - 1) % n].y - y0;
        pnt[(n1 + i) % n].x = cos(theta) * x - sin(theta) * y + x0;
        pnt[(n1 + i) % n].y = sin(theta) * x + cos(theta) * y + y0;
    }

    printf("%.6f %.6f\n", pnt[0].x, pnt[0].y);
    for (int i = n - 1; i > 0; i--) {
        printf("%.6f %.6f\n", pnt[i].x + eps, pnt[i].y + eps);
    }

    return 0;
}
