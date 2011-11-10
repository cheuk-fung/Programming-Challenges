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

using std::sort;
using std::swap;

const int MAX_N = 1000;
const double pi = acos(-1.0);
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y;
    double agl;

    Point() { }
    Point(double _x, double _y) : x(_x), y(_y) { }

    bool operator <(const Point &other) const
    {
        if (eq(y, other.y)) return ls(x, other.x);
        return ls(y, other.y);
    }

    Point operator -(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    double sqlen() const { return x * x + y * y; }
    double length() const { return sqrt(sqlen()); }
};
typedef Point Vec;

inline double cross(const Vec &u, const Vec &v)
{
    return u.x * v.y - u.y * v.x;
}

Point first_ver;

inline bool cmp(const Point &a, const Point &b)
{
    if (eq(a.agl, b.agl))
        return ls((a - first_ver).sqlen(), (b - first_ver).sqlen());
    return ls(a.agl, b.agl);
}

inline bool check(const Point &a, const Point &b, const Point &c)
{
    return cross(b - c, a - c) > eps;
}

double graham_scan(Point *ver, Point *stack, int n, int &top)
{
    int min_ver = 0;
    for (int i = 1; i < n; i++)
        if (ver[i] < ver[min_ver]) min_ver = i;
    swap(ver[0], ver[min_ver]);
    first_ver = ver[0];

    for (int i = 1; i < n; i++)
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);
    sort(ver + 1, ver + n, cmp);

    top = 0;
    stack[top++] = ver[0];
    stack[top++] = ver[1];
    for (int i = 2; i < n; i++) {
        while (top > 1 && !check(ver[i], stack[top - 1], stack[top - 2]))
            top--;
        stack[top++] = ver[i];
    }
    stack[top] = ver[0];

    double res = 0;
    for (int i = 0; i < top; i++)
        res += (stack[i] - stack[i + 1]).length();

    return res;
}

Point ver[MAX_N], stack[MAX_N];
int top;

int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &ver[i].x, &ver[i].y);

    printf("%.0f\n", graham_scan(ver, stack, n, top) + 2.0 * pi * l);

    return 0;
}
