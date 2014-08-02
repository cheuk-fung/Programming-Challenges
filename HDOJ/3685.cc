/*
 *  SRC: HDOJ 3685
 * PROB: Rotational Painting
 * ALGO: Graham Scan
 * DATE: Nov 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;
using std::swap;

const int MAX_N = 50010;
const double eps = 1e-12;

inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y;
    double agl;

    Point(double _x = 0, double _y = 0) : x(_x), y(_y) { }

    bool operator <(const Point &other) const
    {
        if (!eq(y, other.y)) return ls(y, other.y);
        return ls(x, other.x);
    }

    Point operator -(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    double sqlen() const { return x * x + y * y; }
    double length() const { return sqrt(sqlen()); }
};
typedef Point Vec;

inline double dot(const Vec &u, const Vec &v)
{
    return u.x * v.x + u.y * v.y;
}
inline double cross(const Vec &u, const Vec &v)
{
    return u.x * v.y - u.y * v.x;
}

Point ver[MAX_N];
int stack[MAX_N], top;

inline bool cmp(const Point &a, const Point &b)
{
    if (eq(a.agl, b.agl))
        return ls((a - ver[0]).sqlen(), (b - ver[0]).sqlen());
    return ls(a.agl, b.agl);
}

inline bool check(int p)
{
    Vec u = ver[stack[top - 1]] - ver[stack[top - 2]],
        v = ver[p] - ver[stack[top - 2]];
    return cross(u, v) > eps;
}

void graham_scan(int n)
{
    int min_ver = 0;
    for (int i = 1; i < n; i++)
        if (ver[i] < ver[min_ver]) min_ver = i;
    swap(ver[0], ver[min_ver]);

    for (int i = 1; i < n; i++)
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);
    sort(ver + 1, ver + n, cmp);

    top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (int i = 2; i < n; i++) {
        while (top > 1 && !check(i)) top--;
        stack[top++] = i;
    }
    stack[top] = 0;
}

Point g_center(int n) // gravity center
{
    Point res(0, 0);
    ver[n] = ver[0];

    double area = 0;
    for (int i = 1; i <= n; i++) {
        Point &a = ver[i - 1],
              &b = ver[i];
        double t = cross(a, b);
        area += t / 2.0;
        res.x += (a.x + b.x) * t;
        res.y += (a.y + b.y) * t;
    }
    res.x /= (6.0 * area);
    res.y /= (6.0 * area);

    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &ver[i].x, &ver[i].y);

        Point gc = g_center(n);
        graham_scan(n);

        int cnt = 0;
        for (int i = 0; i < top; i++) {
            double a = dot(ver[stack[i + 1]] - ver[stack[i]],
                           gc - ver[stack[i]]),
                   b = dot(ver[stack[i]] - ver[stack[i + 1]],
                           gc - ver[stack[i + 1]]);
            if (gr(a, 0) && gr(b, 0)) cnt++;
        }
        printf("%d\n", cnt);
    }

    return 0;
}
