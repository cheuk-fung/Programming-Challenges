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
#include <algorithm>

using std::swap;

const int MAX_V = 333;
const double eps = 1e-8;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y, z;
    int id;

    Point() { }
    Point(double _x, double _y, double _z, int _id = 0)
        : x(_x), y(_y), z(_z), id(_id)
    { }

    Point operator-(const Point &other) const
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

struct Plane {
    Point p0, p1, p2;

    Plane() { }
    Plane(const Point &_p0, const Point &_p1, const Point &_p2)
        : p0(_p0), p1(_p1), p2(_p2)
    { }

    Vec norm_vec() const
    {
        Vec n = cross(p1 - p0, p2 - p0);
        n.norm();
        return n;
    }
};

inline bool coplaner(const Plane &a, const Plane &b)
{
    return coplaner(a.p0, a.p1, a.p2, b.p0) && \
           coplaner(a.p0, a.p1, a.p2, b.p1) && \
           coplaner(a.p0, a.p1, a.p2, b.p2);
}

inline bool point_above_plane(const Point &p, const Plane &f)
{
    return gr(dot(p - f.p0, f.norm_vec()), 0.0);
}

int edge[MAX_V][MAX_V];
Plane tf[MAX_V];

void convex_hull(Point *ver, Plane *ch, int n, int &ch_cnt)
{
    memset(edge, 0, sizeof(edge));

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

    ch_cnt = 0;
    ch[ch_cnt++] = Plane(ver[0], ver[1], ver[2]);
    ch[ch_cnt++] = Plane(ver[2], ver[1], ver[0]);

    for (int i = 3; i < n; i++) {
        Point curr = ver[i];
        for (int j = 0; j < ch_cnt; j++) {
            Plane f = ch[j];
            if (point_above_plane(curr, f)) {
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
        int tf_cnt = 0;
        for (int j = 0; j < ch_cnt; j++) {
            Plane f = ch[j];
            if (edge[f.p0.id][f.p1.id] == 1) {
                if (edge[f.p1.id][f.p0.id] == -1)
                    tf[tf_cnt++] = Plane(f.p0, f.p1, curr);
                if (edge[f.p2.id][f.p1.id] == -1)
                    tf[tf_cnt++] = Plane(f.p1, f.p2, curr);
                if (edge[f.p0.id][f.p2.id] == -1)
                    tf[tf_cnt++] = Plane(f.p2, f.p0, curr);
            }
            else tf[tf_cnt++] = f;
        }
        for (int i = 0; i < tf_cnt; i++) ch[i] = tf[i];
        ch_cnt = tf_cnt;
    }
}

int cnt_plane(const Plane *ch, int ch_cnt)
{
    int plane_cnt = 0;
    for (int i = 0; i < ch_cnt; i++) {
        bool unique = true;
        for (int j = 0; j < i; j++)
            if (coplaner(ch[i], ch[j])) {
                unique = false;
                break;
            }
        plane_cnt += unique;
    }
    return plane_cnt;
}

double surface_area(const Plane *ch, int ch_cnt)
{
    double s = 0.0;
    for (int i = 0; i < ch_cnt; i++)
        s += 0.5 * cross(ch[i].p1 - ch[i].p0, ch[i].p2 - ch[i].p0).len();
    return s;
}

double volume(const Plane *ch, int ch_cnt)
{
    double v = 0.0;
    const Point O(0, 0, 0);
    for (int i = 0; i < ch_cnt; i++)
        v += dot(cross(ch[i].p0 - O, ch[i].p1 - O), ch[i].p2 - O);
    return fabs(v) / 6.0;
}

Point ver[MAX_V];
Plane ch[MAX_V]; // convex hull, actually, it stores *triangles*

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int ch_cnt = 0;
        for (int i = 0; i < n; i++) {
            double x, y, z;
            scanf("%lf%lf%lf", &x, &y, &z);
            ver[i] = Point(x, y, z, i);
        }

        convex_hull(ver, ch, n, ch_cnt);

        printf("%d\n", cnt_plane(ch, ch_cnt));
    }

    return 0;
}
