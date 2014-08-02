/*
 *  SRC: POJ 3565
 * PROB: Ants
 * ALGO: NULL
 * DATE: Aug 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const double eps = 1e-8;

class Point {
    private:
        int x, y;

    public:
        void read() { scanf("%d%d", &x, &y); }

        Point operator -(const Point& other) const
        {
            Point res;
            res.x = x - other.x;
            res.y = y - other.y;
            return res;
        }
        double operator ^(const Point& other) const { return x * other.y - y * other.x; }
};
typedef Point Vec;

inline bool seg_cross(const Point& a, const Point& b, const Point& c, const Point& d)
{
    Vec m = b - a,
        n = d - c;
    return ((m ^ (c - a)) * (m ^ (d - a)) < eps) && ((n ^ (a - c)) * (n ^ (b - c)) < eps);
}

int main()
{
    int n;
    scanf("%d", &n);
    Point black[n], white[n];
    for (int i = 0; i < n; i++) black[i].read();
    for (int i = 0; i < n; i++) white[i].read();

    int pair[n];
    for (int i = 0; i < n; i++) pair[i] = i;

    while (1 + 1 == 2) {
        bool can_stop = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && seg_cross(black[i], white[pair[i]], black[j], white[pair[j]])) {
                    can_stop = false;

                    int tmp = pair[i];
                    pair[i] = pair[j];
                    pair[j] = tmp;
                }
        if (can_stop) break;
    }

    for (int i = 0; i < n; i++) printf("%d\n", pair[i] + 1);

    return 0;
}

