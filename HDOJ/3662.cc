/*
 *  SRC: HDOJ 3662
 * PROB: 3D Convex Hull
 * ALGO: 3D Convex Hull
 * DATE: Nov 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

using std::vector;
using std::swap;

const int MAX_P = 333;
const double eps = 1e-8;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y, z;
    int id;
    Point(double _x, double _y, double _z, int _id = 0)
        : x(_x), y(_y), z(_z), id(_id)
    { }

    Point operator -(const Point &other) const
    {
        return Point(x - other.x, y - other.y, z - other.z);
    }

    double sqlen() const { return x * x + y * y + z * z; }
    double len() const { return sqrt(sqlen()); }
    void norm() { double l = len(); x /= l; y /= l; z /= l; }
};
typedef Point Vec;

inline double dot(const Vec &u, const Vec &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
inline Vec cross(const Vec &u, const Vec &v)
{
    return Vec(u.y * v.z - u.z * v.y,
               u.z * v.x - u.x * v.z,
               u.x * v.y - u.y * v.x);
}

inline bool coline(const Point &a, const Point &b, const Point &c)
{
    return eq0(cross(b - a, c - a).sqlen());
}
inline bool coplaner(const Point &a, const Point &b, const Point &c, const Point &d)
{
    return eq0(dot(cross(b - a, c - a), d - a));
}

struct Face {
    Point p0, p1, p2;
    Face(const Point &a, const Point &b, const Point &c)
        : p0(a), p1(b), p2(c)
    { }
};

inline bool coplaner(const Face &a, const Face &b)
{
    return coplaner(a.p0, a.p1, a.p2, b.p0) && \
           coplaner(a.p0, a.p1, a.p2, b.p1) && \
           coplaner(a.p0, a.p1, a.p2, b.p2);
}

inline Vec face_normal(const Face &f)
{
    Vec u = f.p1 - f.p0,
        v = f.p2 - f.p0,
        n = cross(u, v);
    n.norm();
    return n;
}

inline bool point_above_face(const Point &p, const Face &f)
{
    Vec u = p - f.p0,
        n = face_normal(f);
    return gr(dot(u, n), 0.0);
}

int edge[MAX_P][MAX_P];
vector<Point> ver;
vector<Face> ch;

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ver.clear();
        ch.clear();
        for (int i = 0; i < n; i++) {
            double x, y, z;
            scanf("%lf%lf%lf", &x, &y, &z);
            ver.push_back(Point(x, y, z, i));
        }

        if (coline(ver[0], ver[1], ver[2]))
            for (int i = 3; i < n; i++) {
                if (!coline(ver[0], ver[1], ver[i])) {
                    swap(ver[2], ver[i]);
                    break;
                }
            }
        if (coplaner(ver[0], ver[1], ver[2], ver[3]))
            for (int i = 4; i < n; i++) {
                if (!coplaner(ver[0], ver[1], ver[2], ver[i])) {
                    swap(ver[3], ver[i]);
                    break;
                }
            }

        ch.push_back(Face(ver[0], ver[1], ver[2]));
        ch.push_back(Face(ver[2], ver[1], ver[0]));

        for (int i = 3; i < ver.size(); i++) {
            Point curr = ver[i];
            for (int j = 0; j < ch.size(); j++) {
                Face f = ch[j];
                if (point_above_face(curr, f)) {
                    edge[f.p0.id][f.p1.id] = 1;
                    edge[f.p1.id][f.p2.id] = 1;
                    edge[f.p2.id][f.p0.id] = 1;
                }
                else {
                    edge[f.p0.id][f.p1.id] = -1;
                    edge[f.p1.id][f.p2.id] = -1;
                    edge[f.p2.id][f.p0.id] = -1;
                }
            }
            vector<Face> tf;
            for (int j = 0; j < ch.size(); j++) {
                Face f = ch[j];
                if (edge[f.p0.id][f.p1.id] == 1) {
                    if (edge[f.p1.id][f.p0.id] == -1)
                        tf.push_back(Face(f.p0, f.p1, curr));
                    if (edge[f.p2.id][f.p1.id] == -1)
                        tf.push_back(Face(f.p1, f.p2, curr));
                    if (edge[f.p0.id][f.p2.id] == -1)
                        tf.push_back(Face(f.p2, f.p0, curr));
                    }
                else tf.push_back(f);
            }
            swap(ch, tf);
        }

        int face_cnt = 0;
        for (int i = 0; i < ch.size(); i++) {
            bool get = true;
            for (int j = 0; j < i; j++)
                if (coplaner(ch[i], ch[j])) {
                    get = false;
                    break;
                }
            face_cnt += get;
        }
        printf("%d\n", face_cnt);
    }

    return 0;
}
