/*
 *  SRC: POJ 1113
 * PROB: Wall
 * ALGO: Graham Scan(Convex Hull)
 * DATE: Jul 26, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
const double pi = acos(-1.0);
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y;
    double agl;

    bool operator<(const Point &o) const { return eq(y, o.y) ? ls(x, o.x) : ls(y, o.y); }
    Point operator-(const Point &o) const { return (Point){x - o.x, y - o.y}; }
    double operator^(const Point &o) const { return x * o.y - y * o.x; }

    double sqlen() const { return x * x + y * y; }
    double length() const { return sqrt(sqlen()); }
};

class Point_cmp {
    private:
        Point first;
    public:
        Point_cmp(const Point &_first) : first(_first) { }
        bool operator()(const Point &a, const Point &b)
        {
            return eq(a.agl, b.agl) ? ls((a - first).sqlen(), (b - first).sqlen()) : ls(a.agl, b.agl);
        }
};

double graham_scan(Point *ver, Point *vstack, int n, int &top)
{
    Point *min_ver = min_element(ver, ver + n);
    swap(ver[0], *min_ver);

    for (int i = 1; i < n; i++) {
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);
    }
    sort(ver + 1, ver + n, Point_cmp(ver[0]));

    top = 0;
    vstack[top++] = ver[0];
    vstack[top++] = ver[1];
    for (int i = 2; i < n; i++) {
        while (top > 1 && (!gr((vstack[top - 1] - vstack[top - 2]) ^ (ver[i] - vstack[top - 2]), 0))) top--;
        vstack[top++] = ver[i];
    }
    vstack[top] = ver[0];

    double res = 0;
    for (int i = 0; i < top; i++)
        res += (vstack[i] - vstack[i + 1]).length();

    return res;
}

Point ver[MAXN], vstack[MAXN];
int top;

int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &ver[i].x, &ver[i].y);

    printf("%.0f\n", graham_scan(ver, vstack, n, top) + 2.0 * pi * l);

    return 0;
}
