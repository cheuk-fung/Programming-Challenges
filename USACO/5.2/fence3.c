/*
ID: os.idea1
LANG: C
TASK: fence3
*/
#include <stdio.h>
#include <math.h>

FILE *fin, *fout;

const double eps = 1e-8;

int n;
double min_x, max_x, min_y, max_y;
double ans_x, ans_y, ans_l;

struct Point {
    double x, y;
};

struct Segment {
    struct Point a, b;
} seg[200];

inline void swap(double *x, double *y) { double t = *x; *x = *y; *y = t; }
inline double fmin(double x, double y) { return x < y ? x : y; }
inline double fmax(double x, double y) { return x > y ? x : y; }
inline double dot(struct Point p0, struct Point p1, struct Point p2)
{
    return (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
}
inline double cross(struct Point p0, struct Point p1, struct Point p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}
inline double dist(struct Point u, struct Point v)
{
    return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}

double calc(double x, double y)
{
    struct Point p;
    p.x = x, p.y = y;

    double res = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (dot(seg[i].a, seg[i].b, p) < 0) res += dist(seg[i].a, p);
        else if (dot(seg[i].b, seg[i].a, p) < 0) res += dist(seg[i].b, p);
        else {
            double length = dist(seg[i].a, seg[i].b);
            if (length == 0) res += dist(p, seg[i].a);
            else res += fabs(cross(seg[i].a, seg[i].b, p)) / length;
        }
    }

    return res;
}

double find(int is_x)
{
    double min_l = 1e10, left, right;
    if (is_x) left = min_x, right = max_x;
    else left = min_y, right = max_y;

    int i;
    for(i = 0; i < 50 && left + eps < right; i++) {
        double p1 = (left + right) / 2.0,
               p2 = (p1 + right) / 2.0,
               len_1, len_2;
        if (is_x) len_1 = calc(p1, ans_y), len_2 = calc(p2, ans_y);
        else len_1 = calc(ans_x, p1), len_2 = calc(ans_x, p2);
        if (len_1 == len_2) {
            min_l = fmin(min_l, len_1);
            break;
        }
        if (len_1 < len_2) {
            right = p2;
            min_l = fmin(min_l, len_1);
        }
        else {
            left = p1;
            min_l = fmin(min_l, len_2);
        }
    }

    ans_l = min_l;

    return left;
}

int main()
{
    fin = fopen("fence3.in", "r");
    fout = fopen("fence3.out", "w");

    fscanf(fin, "%d", &n);

    int i;
    for (i = 0; i < n; i++) {
        fscanf(fin, "%lf%lf%lf%lf", \
               &seg[i].a.x, &seg[i].a.y, &seg[i].b.x, &seg[i].b.y);
        if (seg[i].a.x > seg[i].b.x) swap(&seg[i].a.x, &seg[i].b.x);
        if (seg[i].a.y > seg[i].b.y) swap(&seg[i].a.y, &seg[i].b.y);
        min_x = fmin(min_x, seg[i].a.x);
        max_x = fmax(max_x, seg[i].b.x);
        min_y = fmin(min_y, seg[i].a.y);
        max_y = fmax(max_y, seg[i].b.y);
    }

    ans_x = ans_y = -1;
    for (i = 0; i < 50; i++) {
        double x = find(1),
               y = find(0);

        if (x == ans_x && y == ans_y) break;
        else ans_x = x, ans_y = y;
    }

    fprintf(fout, "%.1f %.1f %.1f\n", ans_x, ans_y, ans_l);

    return 0;
}
