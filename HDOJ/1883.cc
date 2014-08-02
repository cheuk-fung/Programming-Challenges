/*
 *  SRC: HDOJ 1883
 * PROB: Phone Cell
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

const double eps = 0.001;
const double pi = acos(-1.0);

int n, r;

struct Node {
    double ang;
    int offset;

    Node(double _ang, int _offset) : ang(_ang), offset(_offset) { };
    bool operator<(const Node& other) const { return ang < other.ang; }
};

struct Point {
    int x, y;
};
Point p[2000];

inline int sqr(int x) { return x * x; }
inline double sqr(double x) { return x * x; }
inline int sqlen(const Point& a, const Point& b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

int main()
{
    while (scanf("%d%d", &n, &r), n || r) {
        for (int i = 0; i < n; i++) scanf("%d%d", &p[i].x, &p[i].y);

        int best = 0;

        double r_sqr = sqr(r + eps);
        for (int i = 0; i < n; i++) {
            vector<Node> cross;
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                int dist = sqlen(p[i], p[j]);
                if (dist <= r_sqr * 4) {
                    double ang1 = atan2(p[j].y - p[i].y, p[j].x - p[i].x),
                           ang2 = atan2(sqrt(r_sqr - dist / 4.0), sqrt(dist) / 2.0);
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

        printf("It is possible to cover %d points.\n", best + 1);
    }

    return 0;
}
