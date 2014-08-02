/*
 *  SRC: HDOJ 3684
 * PROB: Gunshots
 * ALGO: Graham Scan
 * DATE: Nov 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using std::sort;
using std::swap;

const int MAX_N = 1010;
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline bool lseq(double x, double y) { return x - eps <= y; }

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

struct Bullet {
    Point p;
    Vec v;
};

class Polygon {
    private:
        static Point *start_ver;

        int n;
        Point ver[MAX_N];
        int stack[MAX_N], top;

        static bool cmp(const Point &a, const Point &b)
        {
            if (eq(a.agl, b.agl))
                return ls((a - *start_ver).sqlen(), (b - *start_ver).sqlen());
            return ls(a.agl, b.agl);
        }

        bool check(int p)
        {
            Vec u = ver[stack[top - 1]] - ver[stack[top - 2]],
                v = ver[p] - ver[stack[top - 2]];
            return cross(u, v) > eps;
        }

        bool check_colline(const Vec &a, const Vec &b)
        {
            double d = dot(a, b) / a.length() / b.length();
            return eq(d, 1.0);
        }

    public:
        void input(int _n)
        {
            n = _n;

            for (int i = 0; i < n; i++)
                scanf("%lf%lf", &ver[i].x, &ver[i].y);
        }

        void graham_scan()
        {
            int min_ver = 0;
            for (int i = 1; i < n; i++)
                if (ver[i] < ver[min_ver]) min_ver = i;
            swap(ver[0], ver[min_ver]);
            start_ver = &ver[0];

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

        bool shot(const Bullet &bull)
        {
            for (int i = 0; i < top; i++) {
                double a = cross(ver[stack[i]] - bull.p, bull.v),
                       b = cross(ver[stack[i + 1]] - bull.p, bull.v);
                if (ls(a * b, 0)) return true;

                if (eq0(a))
                    return check_colline(ver[stack[i]] - bull.p, bull.v);
                if (eq0(b))
                    return check_colline(ver[stack[i + 1]] - bull.p, bull.v);

                a = dot(ver[stack[i + 1]] - ver[stack[i]],
                        bull.p - ver[stack[i]]);
                b = dot(ver[stack[i]] - ver[stack[i + 1]],
                        bull.p - ver[stack[i + 1]]);
                if (gr(a, 0) && gr(b, 0)) return false;
            }

            return false;
        }
};
Point *Polygon::start_ver;

Polygon poly[110];
Bullet bull;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int q;
            scanf("%d", &q);
            poly[i].input(q);
            poly[i].graham_scan();
        }

        int m;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%lf%lf%lf%lf", &bull.p.x, &bull.p.y, &bull.v.x, &bull.v.y);

            // big bug below
            int shoots = 0;
            for (int j = 0; j < n; j++)
                if (poly[j].shot(bull)) {
                    if (shoots) putchar(' ');
                    shoots++;
                    printf("HIT %d", j);
                }
            if (shoots) putchar(10);
            else puts("MISS");
        }

        puts("*****");
    }

    return 0;
}
