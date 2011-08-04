/*
 *  SRC: NKOJ
 * TASK: In the dormitory
 * ALGO: Math
 * DATE: 04/01/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<cmath>
#include	<cstdlib>
#include	<climits>

struct Point {
    double x, y, z;

    Point(double xx = 0, double yy = 0, double zz = 0)
        : x(xx), y(yy), z(zz) { }
};

class Vector {
    private:
        double x, y, z;

    public:
        Vector(double xx = 0, double yy = 0, double zz = 0)
            : x(xx), y(yy), z(zz) { }
        Vector(const Point& a, const Point& b)
            : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) { }

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }

        double abs() const { return sqrt(x * x + y * y + z * z); }
        Vector unitize() const { return Vector(x / abs(), y / abs(), z / abs()); }
        friend Vector outer(const Vector&, const Vector&);
        friend double inner(const Vector&, const Vector&);

        bool operator==(const Vector& v) const;
        bool operator!=(const Vector& v) const;
        Vector& operator-=(const Vector&);
        Vector& operator*=(double);

        Vector reflect(const Vector&) const;
};

inline Vector outer(const Vector& a, const Vector& b)
{
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}		/* -----  end of function outer  -----  */

inline double inner(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}		/* -----  end of function inner -----  */

inline bool Vector::operator==(const Vector& v) const
{
    return fabs(x - v.x) < 1e-6 && fabs(y - v.y) < 1e-6 && fabs(z - v.z) < 1e-6;
}		/* -----  end of function Vector::operator==  ----- */

inline bool Vector::operator!=(const Vector& v) const
{
    return !(operator==(v));
}		/* -----  end of function Vector::operator!=  ----- */

inline Vector& Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}		/* -----  end of function Vector::operator-=  ----- */

inline Vector operator-(const Vector& a, const Vector& b)
{
    Vector r = a;
    return r -= b;
}		/* -----  end of function operator-  ----- */

inline Vector& Vector::operator*=(double k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}		/* -----  end of function Vector::operator*=  ----- */

inline Vector operator*(double k, const Vector& v)
{
    Vector r = v;
    return r *= k;
}		/* -----  end of function operator*  ----- */

inline Vector Vector::reflect(const Vector& n) const
{
    return *this - 2 * inner(*this, n.unitize()) * n.unitize();
}		/* -----  end of function Vector::reflect  ----- */

struct Line {
    /*
     *  x = x0 + lt;
     *  y = y0 + mt;
     *  z = z0 + nt;
     *  m(x0, y0, z0)
     *  v = {l, m, n}
     */
    Point m;
    Vector v;

    Line(const Point& mm, const Vector& vv)
        : m(mm), v(vv) { }
};

struct Flat {
    /*  
     *  Ax + By + Cz + D = 0
     *  n = {A, B, c}
     */
    Vector n;
    double D;

    Flat(double AA = 0, double BB = 0, double CC = 0, double DD = 0)
        : n(AA, BB, CC), D(DD) { }
    Flat(const Point& p1, const Point& p2, const Point& p3)
    {
        double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y),
              B = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z),
              C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        n = Vector(A, B, C);
        D = -(A * p1.x + B * p1.y + C * p1.z);
    }
};

struct Triangle {
    Point a, b, c;
    Flat fl;

    Triangle() { }
    Triangle(Point aa, Point bb, Point cc)
        : a(aa), b(bb), c(cc), fl(Flat(aa, bb, cc)) { }
};

bool cross(const Flat& fl, const Line& l, Point* p)
{
    double k = inner(fl.n, l.v);
    if (fabs(k) < 1e-6) return false; // inner(n, v) == 0, namely fl//l
    double t = -(inner(fl.n, Vector(Point(0, 0, 0), l.m)) + fl.D) / k;
    p->x = l.m.x + l.v.getX() * t;
    p->y = l.m.y + l.v.getY() * t;
    p->z = l.m.z + l.v.getZ() * t;
    if (l.v.unitize() != Vector(l.m, *p).unitize()) return false;
    return true;
}

bool inTri(const Triangle& tri, const Point& p)
{
    Vector a = outer(Vector(tri.a, tri.b), Vector(tri.a, p));
    if (a == Vector(0, 0, 0)) return true;
    Vector b = outer(Vector(tri.b, tri.c), Vector(tri.b, p));
    if (b == Vector(0, 0, 0)) return true;
    if (a.unitize() != b.unitize()) return false;
    Vector c = outer(Vector(tri.c, tri.a), Vector(tri.c, p));
    if (c == Vector(0, 0, 0)) return true;
    if (a.unitize() != c.unitize()) return false;
    return true;
}

inline double dis(const Point& a, const Point& b)
{
    return Vector(a, b).abs();
}

const long MAXN = 1000000;
Triangle tri[MAXN];
Flat Floor(0, 1, 0, 0);

void find(int n, Point eye, Vector v)
{
    while (1 + 1 == 2) {
        Line l(eye, v);
        double minDis = LONG_MAX;
        Point minPoi;
        long minTri = -1;
        for (long i = 0; i < n; i++) {
            Point p;
            if (cross(tri[i].fl, l, &p) == false) continue;
            if (inTri(tri[i], p) == false) continue;
            double len = dis(eye, p);
            if (len - minDis < 1e-6) {
                minDis = len;
                minPoi = p;
                minTri = i;
            }
        }
        if (minTri == -1) {
            Point ans;
            if (cross(Floor, l, &ans) == true) printf("%.3f %.3f %.3f\n", ans.x, ans.y, ans.z);
            else printf("Impossible\n");
            return ;
        }
        if (outer(v, tri[minTri].fl.n) == Vector(0, 0, 0)) { // outer(v, n) == 0, namely v//n
            printf("Impossible\n");
            return ;
        }
        eye = minPoi;
        v = v.reflect(tri[minTri].fl.n);
    }
}				/* ----------  end of function find  ---------- */

int main()
{
    long n;
    scanf("%ld", &n);
    for (long i = 0; i < n; i++) {
        double x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z);
        Point a(x, y, z);
        scanf("%lf%lf%lf", &x, &y, &z);
        Point b(x, y, z);
        scanf("%lf%lf%lf", &x, &y, &z);
        Point c(x, y, z);
        tri[i] = Triangle(a, b, c);
    }

    long q;
    scanf("%ld", &q);
    for (long i = 0; i < q; i++) {
        double x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z);
        Point eye(x, y, z);
        scanf("%lf%lf%lf", &x, &y, &z);
        Vector v(x, y, z);
        find(n, eye, v);
    }

    return 0;
}				/* ----------  end of function main  ---------- */

