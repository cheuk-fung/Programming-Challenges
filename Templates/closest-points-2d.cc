/*
 *  SRC: NKOJ 2185
 * PROB: Exercise 5
 * ALGO: D&C
 * DATE: Nov 23, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using std::sort;
using std::min;

const int MAX_P = 30010;

struct Point {
    int id;
    int x, y;
};
Point X[MAX_P], Y[MAX_P], Z[MAX_P];

inline bool cmp_x(const Point &a, const Point &b) { return a.x < b.x; }
inline bool cmp_y(const Point &a, const Point &b) { return a.y < b.y; }
inline int sqr(int x) { return x * x; }
inline int sqr_dist(const Point &a, const Point &b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

void merge(Point *p, Point *q, int left, int mid, int right)
{
    int l = left, r = mid + 1, cnt = left;
    while (l <= mid && r <= right) {
        if (q[l].y < q[r].y) p[cnt++] = q[l++];
        else p[cnt++] = q[r++];
    }
    while (l <= mid)   p[cnt++] = q[l++];
    while (r <= right) p[cnt++] = q[r++];
}

int closest(Point *X, Point *Y, Point *Z, int l, int r) // X[l, r]
{
    if (r - l == 1) return sqr_dist(X[l], X[r]);
    if (r - l == 2) {
        int d1 = sqr_dist(X[l], X[l + 1]),
            d2 = sqr_dist(X[l], X[r]),
            d3 = sqr_dist(X[l + 1], X[r]);
        return min(d1, min(d2, d3));
    }

    int mid = (l + r) / 2;
    for (int i = l, j = l, k = mid + 1; i <= r; i++) {
        if (Y[i].id <= mid) Z[j++] = Y[i];
        else Z[k++] = Y[i];
    }

    int dl = closest(X, Z, Y, l, mid),
        dr = closest(X, Z, Y, mid + 1, r),
        d  = min(dl, dr);
    merge(Y, Z, l, mid, r);

    int z_cnt = l;
    for (int i = l; i <= r; i++)
        if (sqr(abs(X[mid].x - Y[i].x)) < d)
            Z[z_cnt++] = Y[i];

    for (int i = l; i < z_cnt; i++)
        for (int j = i + 1; j < z_cnt && sqr(Z[j].y - Z[i].y) < d; j++)
            d = min(d, sqr_dist(Z[i], Z[j]));

    return d;
}

int closest_pair(Point *X, int n)
{
    sort(X, X + n, cmp_x);
    for (int i = 0; i < n; i++) X[i].id = i;
    memcpy(Y, X, n * sizeof(X[0]));
    sort(Y, Y + n, cmp_y);

    return closest(X, Y, Z, 0, n - 1);
}

int main()
{
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &X[i].x, &X[i].y);

    int ans = closest_pair(X, n);
    printf("%d\n", ans);

    return 0;
}
