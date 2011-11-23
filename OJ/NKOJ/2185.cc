/*
 *  SRC: NKOJ 2185
 * PROB: Exercise 5 平面最近点对
 * ALGO: D&C
 * DATE: Nov 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <algorithm>

using std::sort;
using std::min;

const int MAX_P = 30010;

struct Point {
    int id;
    int x, y;
};
Point X[MAX_P],
      *Y[MAX_P], *Z[MAX_P],
      *bufl[MAX_P << 3], *bufr[MAX_P << 3];
int bufl_cnt, bufr_cnt;

inline bool cmp_x(const Point &a, const Point &b) { return a.x < b.x; }
inline bool cmp_y(const Point *a, const Point *b) { return a->y < b->y; }
inline int sqr(int x) { return x * x; }
inline int sqr_dist(const Point &a, const Point &b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int closest(Point **Y, int l, int r) // X[l, r]
{
    if (r - l == 1) return sqr_dist(X[l], X[r]);
    if (r - l == 2) {
        int d1 = sqr_dist(X[l], X[l + 1]),
            d2 = sqr_dist(X[l], X[r]),
            d3 = sqr_dist(X[l + 1], X[r]);
        return min(d1, min(d2, d3));
    }

    Point **L = &bufl[bufl_cnt],
          **R = &bufr[bufr_cnt];
    int mid = (l + r) / 2;
    for (int i = 0; i <= r - l; i++) {
        if (Y[i]->id <= mid) bufl[bufl_cnt++] = Y[i];
        else bufr[bufr_cnt++] = Y[i];
    }

    int dl = closest(L, l, mid),
        dr = closest(R, mid + 1, r),
        d  = min(dl, dr);

    int z_cnt = 0;
    for (int i = 0; i <= r - l; i++)
        if (sqr(abs(X[mid].x - Y[i]->x)) < d)
            Z[z_cnt++] = Y[i];

    for (int i = 0; i < z_cnt; i++)
        for (int j = i + 1; j < z_cnt && sqr(Z[j]->y - Z[i]->y) < d; j++)
            d = min(d, sqr_dist(*Z[i], *Z[j]));

    return d;
}

int closest_pair(int n)
{
    sort(X, X + n, cmp_x);

    for (int i = 0; i < n; i++) {
        X[i].id = i;
        Y[i] = &X[i];
    }
    sort(Y, Y + n, cmp_y);

    return closest(Y, 0, n - 1);
}

inline int next_int()
{
    char c = '0';
    while (!isdigit(c = getchar())) ;
    int res = c - '0';
    while (isdigit(c = getchar())) res = res * 10 + c - '0';
    return res;
}

int main()
{
    int n = next_int();
    for (int i = 0; i < n; i++) {
        X[i].x = next_int();
        X[i].y = next_int();
    }

    int ans = closest_pair(n);
    printf("%d\n", ans);

    return 0;
}
