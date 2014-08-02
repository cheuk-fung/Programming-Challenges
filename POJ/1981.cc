/*
 *  SRC: POJ 1981
 * PROB: Circle and Points
 * ALGO: NULL
 * DATE: Aug 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;
using std::max;

const double eps = 1e-8;
const double pi = acos(-1.);
const double r_sqr = 1.;

int n, r;

struct Node {
    double ang;
    int offset;

    Node(double _ang, int _offset) : ang(_ang), offset(_offset) { };
    bool operator<(const Node& other) const { return ang < other.ang; }
};

struct Point {
    double x, y;
};
Point p[2000];

inline double sqr(double x) { return x * x; }
inline double sqlen(const Point& a, const Point& b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

int main()
{
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);

        int best = 0;

        for (int i = 0; i < n; i++) {
            vector<Node> cross;
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                double dist = sqlen(p[i], p[j]);
                if (dist <= r_sqr * 4) {
                    double ang1 = atan2(p[j].y - p[i].y, p[j].x - p[i].x),
                           ang2 = atan2(sqrt(r_sqr - dist / 4.), sqrt(dist) / 2.);
                    cross.push_back(Node(ang1 + ang2, -1));
                    cross.push_back(Node(ang1 - ang2, 1));
                }
            }
            sort(cross.begin(), cross.end());
            int cnt = 0;
            for (vector<Node>::const_iterator vi = cross.begin(); vi != cross.end(); vi++) {
                cnt += vi->offset;
                best = max(best, cnt);
            }
        }

        printf("%d\n", best + 1);
    }

    return 0;
}
