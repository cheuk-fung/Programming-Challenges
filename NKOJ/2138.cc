/*
 *  SRC: NKOJ 2138
 * PROB: Fractal
 * ALGO: Computational Geometry
 * DATE: Aug 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <complex>

using std::complex;

typedef complex<double> Complex;
const double eps = 1e-12;

int n, d;
double f, scale;
double totLen, currLen, target;

struct Point {
    double x, y;

    Point operator-(const Point& other) const
    {
        Point r;
        r.x = x - other.x;
        r.y = y - other.y;
        return r;
    }
};
Point p[100];

struct Line {
    Point st;
    Complex vec;

    double getX()
    {
        return st.x + vec.real();
    }
    double getY()
    {
        return st.y + vec.imag();
    }
};
Line line[100];

inline double norm(const Point& c)
{
    return sqrt(c.x * c.x + c.y * c.y);
}

bool dfs(int depth, Line* prev)
{
    if (depth == d) return false;

    Line curr[n - 1];
    for (int i = 0; i + 1 < n; i++) {
        curr[0].st = prev[i].st;
        curr[0].vec = Complex(prev[i].vec * scale);

        for (int j = 0; j + 1 < n; j++) {
            if (j > 0) {
                curr[j].st.x = curr[j - 1].getX();
                curr[j].st.y = curr[j - 1].getY();
                curr[j].vec = line[j].vec * curr[0].vec / line[0].vec;
            }

            Point t;
            t.x = curr[j].vec.real();
            t.y = curr[j].vec.imag();
            double tLen = norm(t);

            if (depth + 1 == d) {
                currLen += tLen;
                if (fabs(currLen - target) < eps) {
                    double x = prev[n - 2].getX(),
                           y = prev[n - 2].getY();
                    printf("(%.10f,%.10f)\n", x, y);
                    return true;
                }
                if (currLen - eps > target) {
                    currLen -= tLen;
                    double rate = (target - currLen) / tLen;
                    double x = curr[j].st.x + curr[j].vec.real() * rate,
                           y = curr[j].st.y + curr[j].vec.imag() * rate;
                    printf("(%.10f,%.10f)\n", x, y);
                    return true;
                }
            }
        }

        if (dfs(depth + 1, curr)) return true;
    }

    return false;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);

    while (jobs--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        scanf("%d%lf", &d, &f);

        totLen = currLen = 0;
        for (int i = 0; i + 1 < n; i++) {
            Point t = p[i + 1] - p[i];
            line[i].st = p[i];
            line[i].vec = Complex(t.x, t.y);
            totLen += norm(t);
        }
        scale = norm(p[1] - p[0]) / norm(p[n - 1] - p[0]);

        double seDis = norm(p[n - 1] - p[0]),
               rate = totLen / seDis;
        for (int i = 1; i < d; i++) totLen *= rate;
        target = totLen * f;
        dfs(1, line);
    }

    return 0;
}
