/*
 * =====================================================================================
 * 
 *       Filename:  Vector.cc
 * 
 *    Description:  A class for calculating Vectors.
 * 
 *        Created:  04/01/2011 23:52:35
 *       Compiler:  g++
 * 
 *         Author:  Leewings Ac (Zhuofeng Wu), osideal {at} gmail.com
 * 
 * =====================================================================================
 */

/*
 * #include	<cmath>
 * #include	<cstdlib>
 */

namespace Vec {
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

    Vector operator-(const Vector& a, const Vector& b)
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

    Vector operator*(double k, const Vector& v)
    {
        Vector r = v;
        return r *= k;
    }		/* -----  end of function operator*  ----- */

    inline Vector Vector::reflect(const Vector& n) const
    {
        return *this - 2 * inner(*this, n.unitize()) * n.unitize();
    }		/* -----  end of function Vector::reflect  ----- */

    inline double dis(const Point& a, const Point& b)
    {
        return Vector(a, b).abs();
    }

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
         *  n = {A, B, c} and A^2 + B^2 + C^2 = 1
         */
        Vector n;
        double D;

        Flat(double AA = 0, double BB = 0, double CC = 0, double DD = 0)
            : n(AA, BB, CC), D(DD) { }
        Flat(const Vector& nn, const Point& p)
            : n(nn)
        {
            D = -(n.getX() * p.x + n.getY() * p.y + n.getZ() * p.z);
        }
        Flat(const Point& p1, const Point& p2, const Point& p3)
        {
            double A = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y),
                  B = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z),
                  C = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
            n = Vector(A, B, C);
            D = -(A * p1.x + B * p1.y + C * p1.z);
        }
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
}		/* -----  end of namespace Vec ----- */

