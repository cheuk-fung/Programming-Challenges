/*
 *  SRC: HDOJ 2773
 * PROB: White Water Rafting
 * ALGO: Computational Geometry
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

const double eps = 1e-12;

struct Point {
    int x, y;

    Point operator-(const Point& other) const
    {
        Point res;
        res.x = x - other.x;
        res.y = y - other.y;
        return res;
    }
    int operator*(const Point& other) const { return x * other.x + y * other.y; }
    int operator^(const Point& other) const { return x * other.y - y * other.x; }

    double len() const { return sqrt(x * x + y * y); }
};

inline double dist2seg(const Point& p, const Point& o, const Point& k)
{
    if ((p - o)*(k - o) < 0) return (p - o).len();
    if ((p - k)*(o - k) < 0) return (p - k).len();
    return abs((p - o)^(o - k)) / (o - k).len();
}

Point inner[101], outer[102];

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        int n, m;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &inner[i].x, &inner[i].y);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d%d", &outer[i].x, &outer[i].y);
        outer[m] = outer[0];

        double ans = 1e8;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                double curr = dist2seg(inner[i], outer[j], outer[j + 1]);
                if (curr + eps < ans) ans = curr;
            }

        printf("%.10f\n", ans / 2.0);
    }

    return 0;
}
