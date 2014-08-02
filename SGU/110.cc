#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const double DINF = 1e20;
const double eps = 1e-10;

inline bool gr(double x, double y) { return x - eps > y; }
inline bool greq(double x, double y) { return x + eps >= y; }

class Point {
    public:
        double x, y, z;

        Point() { }
        Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }

        Point operator+(const Point &v) const { return Point(x + v.x, y + v.y, z + v.z); }
        Point operator-(const Point &v) const { return Point(x - v.x, y - v.y, z - v.z); }
        Point operator^(const Point &v) const { return Point(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
        Point operator*(double k) const { return Point(k * x, k * y, k * z); }
        double operator*(const Point &v) const { return x * v.x + y * v.y + z * v.z; }

        double sqlen() const { return x * x + y * y + z * z; }
        double len() const { return sqrt(sqlen()); }
        Point norm() const { return Point(x / len(), y / len(), z / len()); }

        Point reflect(const Point &n) const
        {
            Point v(-x, -y, -z);
            return n.norm() * (v * n.norm()) * 2 - v;
        }
};
typedef Point Vec;

class Sphere {
    public:
        Point c;
        double r;

        bool inside(const Point &p) const { return greq(r, (p - c).len()); }
} spheres[50];

vector<int> ans;

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf%lf", &spheres[i].c.x, &spheres[i].c.y, &spheres[i].c.z, &spheres[i].r);
    }

    Point start, end;
    scanf("%lf%lf%lf%lf%lf%lf", &start.x, &start.y, &start.z, &end.x, &end.y, &end.z);

    int now = -1;
    Vec incidence = end - start;
    while (ans.size() <= 10) {
        int reflect_id = -1;
        double dmin = DINF;
        for (int i = 0; i < n; i++) {
            if (i == now) continue;

            double h = (incidence ^ (spheres[i].c - start)).len() / incidence.len();
            if (gr(h, spheres[i].r)) continue;
            double l = sqrt((spheres[i].c - start).sqlen() - h * h);
            for (int k = 1; ; k = -1) {
                double d = l - sqrt(spheres[i].r * spheres[i].r - h * h) * k;
                if (gr(dmin, d)) {
                    Point candidate = start + incidence.norm() * d;
                    if (spheres[i].inside(candidate)) {
                        end = candidate;
                        dmin = d;
                        reflect_id = i;
                    }
                }
                if (k == -1) break;
            }
        }
        if (reflect_id == -1) break;

        now = reflect_id;
        ans.push_back(reflect_id + 1);
        start = end;
        incidence = incidence.reflect(end - spheres[reflect_id].c);
    }

    if (ans.size()) {
        printf("%d", ans[0]);
        for (int i = 1; i < min((int)ans.size(), 10); i++) {
            printf(" %d", ans[i]);
        }
        if (ans.size() > 10) {
            printf(" etc.");
        }
        putchar(10);
    }

    return 0;
}
