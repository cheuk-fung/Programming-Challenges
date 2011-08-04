/*
 *  SRC: NKOJ p1219
 * PROB: Triangle
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

const double eps = 1e-12;

inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }

const int MAX_N = 50005;

struct Point {
    int x, y;
    double agl;

    Point() { }
    Point(int _x, int _y) : x(_x), y(_y) { }

    bool operator<(const Point& other) const
    {
        return y < other.y || (y == other.y && x < other.x);
    }

    int sqlen(const Point& other) const { return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y); }
} ver[MAX_N];

typedef Point Vec;

inline int cross(const Vec& a, const Vec& b, const Vec& c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

int n, min;
int stack[MAX_N], top;

inline bool cmp(const Point& a, const Point& b)
{
    if (eq(a.agl, b.agl))
        return ver[0].sqlen(a) < ver[0].sqlen(b);
    return ls(a.agl, b.agl);
}

void grahamScan()
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

    top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (int i = 2; i < n; i++) {
        while (top > 1 && cross(ver[stack[top - 2]], ver[stack[top - 1]], ver[i]) <= 0) top--;
        stack[top++] = i;
    }
}

int calc(int i, int j)
{
    int res = 0, left = j + 1, right = top;
    while (left < right) {
        int p1 = (left + right) / 2,
            p2 = (p1 + right) / 2,
            area1 = cross(ver[stack[i]], ver[stack[j]], ver[stack[p1]]),
            area2 = cross(ver[stack[i]], ver[stack[j]], ver[stack[p2]]);
        if (area1 < area2) {
            left = p1;
            if (area2 > res) res = area2;
        }
        else {
            right = p2;
            if (area1 > res) res = area1;
        }
    }

    return res;
}

double findMax()
{
    int res = 0;
    for (int i = 0; i < top; i++)
        for (int j = i + 1; j < top; j++) {
            int t = calc(i, j);
            if (t > res) res = t;
        }

    return res / 2.0;
}

int main()
{
    while (scanf("%d", &n) == 1 && n != -1) {
        for (int i = 0; i < n;i ++)
            scanf("%d%d", &ver[i].x, &ver[i].y);

        grahamScan();
        printf("%.2f\n", findMax());
    }

    return 0;
}

