/*
 *  SRC: HDOJ 4036
 * PROB: Rolling Hongshu
 * ALGO: Physics
 * DATE: Sep 11, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;
using std::max;

const double g = 20;

struct Point {
    double x, y, k;
} hill[1010];

struct Potato {
    double p, v, m;
    int h;

    bool operator <(const Potato &other) const { return p < other.p; }
} po[1010];

int n, m, w;

void work()
{
    scanf("%d%d%d", &n, &m, &w);
    double max_h = -1e10;
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &hill[i].x, &hill[i].y);
        max_h = max(max_h, hill[i].y);
    }
    for (int i = 0; i < m; i++)
        scanf("%lf%lf%lf", &po[i].p, &po[i].v, &po[i].m);
    sort(po, po + m);

    for (int i = 0, h = 0; i < m; i++) {
        while (po[i].p > hill[h].x) h++;
        po[i].h = h;
        po[i].p -= hill[h - 1].x;
    }

    for (int i = n - 1; i > 0; i--)
        hill[i].k = (hill[i].y - hill[i - 1].y) / (hill[i].x - hill[i - 1].x);

    double min_e = g * max_h;
    for (int i = 0; i < m; i++) {
        double h = po[i].p * hill[po[i].h].k + hill[po[i].h - 1].y,
               e = g * h + po[i].v * po[i].v / 2.0;
        min_e = max(min_e, e);
    }
    double min_v = min_e < g * hill[0].y ? 0 : sqrt((min_e - g * hill[0].y) * 2);

    printf("%.2f\n", min_v);
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    for (int i = 1; i <= jobs; i++) {
        printf("Case %d: ", i);
        work();
    }

    return 0;
}
