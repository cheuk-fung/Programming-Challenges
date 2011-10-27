/*
ID: os.idea1
LANG: C
TASK: fc
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 10010

FILE *fin, *fout;

const double eps = 1e-12;

struct Point {
    double x, y;
    double agl;
} ver[MAX_N];

int n, min;
int stack[MAX_N], top;

inline int eq0(double x) { return fabs(x) < eps; }
inline int eq(double x, double y) { return fabs(x - y) < eps; }
inline int ls(double x, double y) { return x + eps < y; }
inline int gr(double x, double y) { return x - eps > y; }

inline double sqlen(const struct Point a) { return a.x * a.x + a.y * a.y; }
inline double length(const struct Point a) { return sqrt(sqlen(a)); }

inline int lspo(const struct Point a, const struct Point b)
{
    if (!eq(a.y, b.y)) return ls(a.y, b.y);
    return ls(a.x, b.x);
}

inline struct Point minus(const struct Point a, const struct Point b)
{
    return (struct Point){a.x - b.x, a.y - b.y};
}

inline double cross(const struct Point u, const struct Point v)
{
    return u.x * v.y - u.y * v.x;
}

inline int cmp(const void *a, const void *b)
{
    double p = ((const struct Point *)a)->agl,
           q = ((const struct Point *)b)->agl;
    if (eq(p, q)) {
        p = sqlen(minus(*(const struct Point *)a ,ver[0])),
          q = sqlen(minus(*(const struct Point *)b ,ver[0]));
        if (gr(p, q)) return 1;
        if (eq(p, q)) return 0;
        return -1;
    }

    if (gr(p, q)) return 1;
    return -1;
}

inline int check(int i)
{
    struct Point u = minus(ver[stack[top - 1]], ver[stack[top - 2]]),
                 v = minus(ver[i], ver[stack[top - 2]]);
    return cross(u, v) > eps;
}

double grahamScan()
{
    int i;

    min = 0;
    for (i = 1; i < n; i++)
        if (lspo(ver[i], ver[min])) min = i;

    struct Point t = ver[0];
    ver[0] = ver[min];
    ver[min] = t;

    for (i = 1; i < n; i++)
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);

    qsort(ver + 1, n - 1, sizeof(struct Point), cmp);

    top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (i = 2; i < n; i++) {
        while (top > 1 && !check(i)) top--;
        stack[top++] = i;
    }

    double res = 0;
    for (i = 0; i < top - 1; i++)
        res += length(minus(ver[stack[i]], ver[stack[i + 1]]));
    res += length(minus(ver[stack[top - 1]], ver[0]));

    return res;
}

int main()
{
    fin = fopen("fc.in", "r");
    fout = fopen("fc.out", "w");

    fscanf(fin, "%d", &n);

    int i;
    for (i = 0; i < n; i++)
        fscanf(fin, "%lf%lf", &ver[i].x, &ver[i].y);

    fprintf(fout, "%.2f\n", grahamScan());

    return 0;
}
