/*
 *  SRC: POJ 2187
 * PROB: Beauty Contest
 * ALGO: Rotating Calipers
 * DATE: Nov 09, 2011 
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

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline double fmax(double x, double y) { return gr(x, y) ? x : y; }

struct Point {
    double x, y;
    double agl;

    Point() { }
    Point(double _x, double _y) : x(_x), y(_y) { }

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

inline double dist(const Point &u, const Point &v)
{
    return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
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

double rotating_calipers(int n)
{
    double res = 0.0;
    for (int curr = 0, next = 1; curr < n; curr++) {
        while (gr(cross(ver[stack[curr + 1]] - ver[stack[curr]],
                        ver[stack[next + 1]] - ver[stack[curr]]),
                  cross(ver[stack[curr + 1]] - ver[stack[curr]],
                        ver[stack[next]] - ver[stack[curr]])))
            next = (next + 1) % n;
        res = fmax(res, dist(ver[stack[curr]], ver[stack[next]]));
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &ver[i].x, &ver[i].y);

    graham_scan(n);
    double ans = rotating_calipers(top);
    printf("%.0f\n", ans * ans);

    return 0;
}
