/*
 *  SRC: POJ 2002
 * PROB: Squares
 * ALGO: Geometry
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>

using std::vector;

struct Point {
    int x, y;

    Point() { }
    Point(int _x, int _y) : x(_x), y(_x) { }
} star[1000];

int n;
vector<int> xy[40010];

inline Point rotateLeft(Point p1, Point p2)
{
    Point p;
    p.x = p1.x - (p2.y - p1.y);
    p.y = p1.y + (p2.x - p1.x);

    return p;
}

inline Point rotateRight(Point p1, Point p2)
{
    Point p;
    p.x = p1.x + (p2.y - p1.y);
    p.y = p1.y - (p2.x - p1.x);

    return p;
}

inline int exist(int x, int y)
{
    x += 20000;
    for (int i = 0; i < xy[x].size(); i++)
        if (xy[x][i] == y) return 1;

    return 0;
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;

        for (int i = 0; i < 40010; i++) xy[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &star[i].x, &star[i].y);
            xy[star[i].x + 20000].push_back(star[i].y);
        }

        long long cnt = 0;
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++) {
                Point a, b;
                a = rotateLeft(star[i], star[j]);
                if (exist(a.x, a.y)) {
                    b = rotateLeft(a, star[i]);
                    if (exist(b.x, b.y))
                        cnt++;
                }

                a = rotateRight(star[i], star[j]);
                if (exist(a.x, a.y)) {
                    b = rotateRight(a, star[i]);
                    if (exist(b.x, b.y))
                        cnt++;
                }
            }

        printf("%lld\n", cnt / 4);
    }

    return 0;
}
