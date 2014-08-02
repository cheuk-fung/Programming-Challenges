/*
 *  SRC: POJ 1228
 * PROB: Grandpa's Estate
 * ALGO: Graham Scan
 * DATE: Jul 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;

const double pi = acos(-1.0);
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

const int MAX_N = 1000;

struct Point {
    double x, y;
    double agl;

    Point() { }
    Point(double _x, double _y) : x(_x), y(_y) { }

    bool operator<(const Point& other) const
    {
        if (!eq(y, other.y)) return ls(y, other.y);
        return ls(x, other.x);
    }

    Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }

    double length() const { return sqrt(x * x + y * y); }
} ver[MAX_N];

typedef Point Vec;

inline double cross(const Vec& u, const Vec& v){ return u.x * v.y - u.y * v.x; }
inline bool coline(const Point& a, const Point& b, const Point& c){ return eq0(cross(b - a, c - a)); }

int n, min;
int stack[MAX_N], top;

inline bool cmp(const Point& a, const Point& b)
{
    if (eq(a.agl, b.agl))
        return ls((a - ver[0]).length(), (b - ver[0]).length());
    return ls(a.agl, b.agl);
}

inline bool check(int i)
{
    Vec u = ver[stack[top - 1]] - ver[stack[top - 2]],
        v = ver[i] - ver[stack[top - 2]];
    return cross(u, v) > eps;
}

bool grahamScan()
{
    min = 0;
    for (int i = 1; i < n; i++)
        if (ver[i] < ver[min]) min = i;

    Vec t = ver[0];
    ver[0] = ver[min];
    ver[min] = t;

    for (int i = 1; i < n; i++)
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);
    sort(ver + 1, ver + n, cmp);

    if (!eq(ver[n - 1].agl, ver[n - 2].agl)) return false;

    top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (int i = 2; i < n; i++) {
        while (top > 1 && !check(i)) top--;
        stack[top++] = i;
    }

    if (top == 2) return false;
    for (int i = 1; i < top - 1; i++)
        if (stack[i] - stack[i - 1] < 2) return false;

    return true;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &ver[i].x, &ver[i].y);

        puts(grahamScan() ? "YES" : "NO");
    }

    return 0;
}

