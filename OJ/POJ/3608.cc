/*
 *  SRC: POJ 3608
 * PROB: Bridge Across Islands
 * ALGO: Rotating Calipers
 * DATE: Nov 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;
using std::swap;

const int MAX_N = 10010;
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline double fmin(double x, double y) { return ls(x, y) ? x : y; }

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

    bool operator >(const Point &other) const
    {
        if (eq(y, other.y)) return gr(x, other.x);
        return gr(y, other.y);
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

inline double dot(const Vec &u, const Vec &v)
{
    return u.x * v.x + u.y * v.y;
}

// dist from Point u to Point v
inline double dist(const Point &u, const Point &v)
{
    return (u - v).length();
}

// dist from Point v to Segment ab
inline double dist(const Point &v, const Point &a, const Point &b)
{
    if (ls(dot(v - a, b - a), 0.0)) return dist(v, a);
    if (ls(dot(v - b, a - b), 0.0)) return dist(v, b);
    double area = fabs(cross(v - a, b - a));
    if (eq0(area)) return fmin(dist(v, a), dist(v, b));
    return area / dist(a, b);
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

void graham_scan(Point *ver, Point *stack, int n, int &top)
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
}

double rotating_calipers(const Point *p, const Point *q, int p_top, int q_top)
{
    int p_iter = 0, q_iter = 0;
    for (int i = 1; i < q_top; i++)
        if (q[i] > q[q_iter]) q_iter = i;
    double res = dist(p[p_iter], q[q_iter]);

    int p_init = p_iter, q_init = q_iter;
    do {
        double judge = cross(p[p_iter + 1] - p[p_iter],
                             q[q_iter + 1] - q[q_iter]);
        if (eq0(judge)) {
            res = fmin(res, dist(p[p_iter], q[q_iter], q[q_iter + 1]));
            res = fmin(res, dist(p[p_iter + 1], q[q_iter], q[q_iter + 1]));
            res = fmin(res, dist(q[q_iter], p[p_iter], p[p_iter + 1]));
            res = fmin(res, dist(q[q_iter + 1], p[p_iter], p[p_iter + 1]));
            p_iter = (p_iter + 1) % p_top;
            q_iter = (q_iter + 1) % q_top;
        }
        else if (ls(judge, 0.0)) {
            res = fmin(res, dist(q[q_iter], p[p_iter], p[p_iter + 1]));
            p_iter = (p_iter + 1) % p_top;
        }
        else {
            res = fmin(res, dist(p[p_iter], q[q_iter], q[q_iter + 1]));
            q_iter = (q_iter + 1) % q_top;
        }
    } while (!(p_iter == p_init && q_iter == q_init)) ;

    return res;
}

Point ver[MAX_N], p_stack[MAX_N], q_stack[MAX_N];
int p_top, q_top;

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m), n && m) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &ver[i].x, &ver[i].y);
        graham_scan(ver, p_stack, n, p_top);

        for (int i = 0; i < m; i++)
            scanf("%lf%lf", &ver[i].x, &ver[i].y);
        graham_scan(ver, q_stack, m, q_top);

        double ans = rotating_calipers(p_stack, q_stack, p_top, q_top);
        printf("%.5f\n", ans);
    }

    return 0;
}
