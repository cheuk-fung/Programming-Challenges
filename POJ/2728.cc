/*
 *  SRC: POJ 2728
 * PROB: Desert King
 * ALGO: Optimum Ratio Spanning Tree
 * DATE: Jul 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const double DINF = 1e20;
const double eps = 1e-6;

double tc[MAXN * MAXN];
double cost[MAXN][MAXN];
double length[MAXN][MAXN];
double dist[MAXN];

inline bool ls(double x, double y) { return x + eps < y; }
inline bool lseq(double x, double y) { return x - eps <= y; }

struct Village {
    double x, y, z;
};
Village vil[MAXN];

inline int sqr(int x) { return x * x; }
inline double calcdist(const Village &a, const Village &b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

bool check(double x, int n)
{
    double sum = 0;
    fill(dist, dist + n, DINF);
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        int now;
        double mind = DINF;
        for (int j = 0; j < n; j++) {
            if (dist[j] > -DINF && ls(dist[j], mind)) {
                mind = dist[j];
                now = j;
            }
        }
        sum += mind;
        dist[now] = -DINF;
        for (int j = 0; j < n; j++) {
            double d = cost[now][j] - x * length[now][j];
            if (ls(d, dist[j])) {
                dist[j] = d;
            }
        }
    }

    return lseq(sum, 0);
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int ecnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf%lf", &vil[i].x, &vil[i].y, &vil[i].z);
            for (int j = 0; j < i; j++) {
                cost[i][j] = cost[j][i] = fabs(vil[i].z - vil[j].z);
                length[i][j] = length[j][i] = calcdist(vil[i], vil[j]);
                tc[ecnt++] = cost[i][j];
            }
        }
        sort(tc, tc + ecnt);
        double l = 0, r = 0;
        for (int i = ecnt - 1, j = 0; j < n - 1; i--, j++) r += tc[i];
        r /= n - 1;
        while (ls(l, r)) {
            double mid = (l + r) / 2;
            if (check(mid, n)) r = mid;
            else l = mid;
        }

        printf("%.3f\n", r);
    }

    return 0;
}

