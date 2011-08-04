/*
 *  SRC: NKOJ p1257
 * PROB: EXOCENTER OF A TRIANGLE
 * ALGO: Computational geometry
 * DATE: Jul 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

struct Point {
    double x, y;

    Point() { }
    Point(double _x, double _y) : x(_x), y(_y) { }

    Point operator - (const Point& other) const
    {
        return Point(x - other.x, y - other.y);
    }

    Point rotateCCW(const Point& other) const
    {
        return Point(x - (other.y - y), y + (other.x - x));
    }

    Point rotateCW(const Point& other) const
    {
        return Point(x + (other.y - y), y - (other.x - x));
    }

    Point mid(const Point& other) const
    {
        return Point(x + (other.x - x) / 2.0, y + (other.y - y) / 2.0);
    }
};

typedef Point Vec;

inline double cross(const Vec& a, const Vec& b)
{
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Point a, b;
    Vec l;
    Line(Point _a, Point _b) : a(_a), b(_b), l(_a - _b) { }
};

inline Point lineIntersect(Line& n, Line& m)
{
    double ratio = cross(n.a - m.a, m.l) / cross(n.l, m.l);
    return Point((n.b.x -n.a.x) * ratio + n.a.x, (n.b.y -n.a.y) * ratio + n.a.y);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        Point A, B, C;
        scanf("%lf%lf", &A.x, &A.y);
        scanf("%lf%lf", &B.x, &B.y);
        scanf("%lf%lf", &C.x, &C.y);

        Point D = A.rotateCCW(B), E = B.rotateCW(A),
              G = A.rotateCW(C),  J = B.rotateCCW(C),
              L = G.mid(D),       M = J.mid(E);
        Line LA(L, A), MB(M, B);
        Point O = lineIntersect(LA, MB);

        printf("%.4f %.4f\n", O.x, O.y);
    }

    return 0;
}
