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
#include <cmath>
#include <algorithm>

using namespace std;

enum {
    MAX_P = 30000,
    INF = 0x3f3f3f3f
};

struct Point {
    int x, y;
};
Point X[MAX_P], Y[MAX_P];

inline bool cmp_x(const Point &a, const Point &b) { return a.x < b.x; }
inline bool cmp_y(const Point &a, const Point &b) { return a.y < b.y; }
inline int sqr(int x) { return x * x; }
inline int sqr_dist(const Point &a, const Point &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

int closest(int l, int r) // X[l, r)
{
    if (l + 1 == r) return INF;
    if (l + 2 == r) return sqr_dist(X[l], X[l + 1]);

    int mid = (l + r) >> 1;
    int dl = closest(l, mid),
        dr = closest(mid, r),
        d  = min(dl, dr);


    int cnt = 0;
    for (int i = l; i < r; i++) {
        if (sqr(X[i].x - X[mid].x) < d) {
            Y[cnt++] = X[i];
        }
    }
    sort(Y, Y + cnt, cmp_y);

    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt && sqr(Y[j].y - Y[i].y) < d; j++) {
            d = min(d, sqr_dist(Y[i], Y[j]));
        }
    }

    return d;
}

int next_int()
{
    char c;
    while (isspace(c = getchar())) ;
    int r = c - '0';
    while (isdigit(c = getchar())) r = r * 10 + c - '0';
    return r;
}

int main()
{
    int n = next_int();
    for (int i = 0; i < n; i++){
        X[i].x = next_int();
        X[i].y = next_int();
    }

    sort(X, X + n, cmp_x);
    int ans = closest(0, n);
    printf("%d\n", ans);

    return 0;
}
