/*
 *  SRC: HDOJ 3890
 * PROB: Apparent Magnitude
 * ALGO: BIT
 * DATE: Jul 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
const int MAXM = 20010;
const double eps = 1e-8;

struct Point {
    int x, y;
    int newy;
    double apmag;
    int id;
};
Point pnt[MAXN];

struct Rectangle {
    int x1, y1, x2, y2;
    int newy1, newy2;
    int star1, star2;
    double apmag1, apmag2;

    bool flag;
};
Rectangle rec[MAXM];

template<typename T>
class BIT {
    public:
        T c[MAXN];

        void reset() { memset(c, 0, sizeof(c)); }
        int lowbit(int x) { return x & -x; }

        void update(int x, T v)
        {
            for ( ; x < MAXN; c[x] += v, x += lowbit(x))
                ;
        }
        T sum(int x)
        {
            T res = 0;
            for ( ; x; res += c[x], x -= lowbit(x))
                ;
            return res;
        }
};
BIT<int> star_cnt;
BIT<double> apmag_sum;

int cmp_x(const Point &a, const Point &b)
{
    return a.x == b.x ? a.id == b.id ? a.y < b.y : a.id < b.id : a.x < b.x;
}
int cmp_y(const Point &a, const Point &b) { return a.y < b.y; }

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        star_cnt.reset();
        apmag_sum.reset();

        int pnt_cnt = n;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%lf", &pnt[i].x, &pnt[i].y, &pnt[i].apmag);
            pnt[i].id = MAXN;
        }
        for (int i = 0; i < m; i++) {
            rec[i].flag = true;
            rec[i].newy1 = rec[i].newy2 = -1;

            scanf("%d%d%d%d", &rec[i].x1, &rec[i].y1, &rec[i].x2, &rec[i].y2);
            pnt[pnt_cnt].x = rec[i].x1;
            pnt[pnt_cnt].y = rec[i].y1;
            pnt[pnt_cnt++].id = i + 1;
            pnt[pnt_cnt].x = rec[i].x2;
            pnt[pnt_cnt].y = rec[i].y2;
            pnt[pnt_cnt++].id = i + 1 + MAXN;
        }
        sort(pnt, pnt + pnt_cnt, cmp_y);

        pnt[0].newy = 1;
        for (int i = 1; i < pnt_cnt; i++) {
            pnt[i].newy = pnt[i - 1].newy + (pnt[i].y != pnt[i - 1].y);
            if (pnt[i].id != MAXN) {
                int id = (pnt[i].id % MAXN) - 1;
                if (rec[id].newy1 == -1) {
                    rec[id].newy1 = pnt[i].newy;
                } else {
                    rec[id].newy2 = pnt[i].newy;
                }
            }
        }
        sort(pnt, pnt + pnt_cnt, cmp_x);

        for (int i = 0; i < pnt_cnt; i++) {
            if (pnt[i].id == MAXN) {
                star_cnt.update(pnt[i].newy, 1);
                apmag_sum.update(pnt[i].newy, pnt[i].apmag);
            } else {
                int id = (pnt[i].id % MAXN) - 1;
                if (rec[id].flag) {
                    rec[id].star1 = star_cnt.sum(rec[id].newy1 - 1);
                    rec[id].star2 = star_cnt.sum(rec[id].newy2);
                    rec[id].apmag1 = apmag_sum.sum(rec[id].newy1 -1);
                    rec[id].apmag2 = apmag_sum.sum(rec[id].newy2);
                    rec[id].flag = false;
                } else {
                    rec[id].star1 += star_cnt.sum(rec[id].newy2);
                    rec[id].star2 += star_cnt.sum(rec[id].newy1 - 1);
                    rec[id].apmag1 += apmag_sum.sum(rec[id].newy2);
                    rec[id].apmag2 += apmag_sum.sum(rec[id].newy1 -1);
                }
            }
        }

        for (int i = 0; i < m; i++) {
            printf("%.2lf/%d\n", rec[i].apmag1 - rec[i].apmag2 + eps, rec[i].star1 - rec[i].star2);
        }
    }

    return 0;
}

