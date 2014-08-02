/*
 *  SRC: HDOJ ACM Steps
 * PROB: FatMouse' Trade
 * ALGO: sort
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

struct Room {
    double j, f;

    double v() const { return j / f; }

    bool operator < (const Room &other) const
    {
        return v() > other.v();
    }
};

Room rooms[1010];

int main()
{
    while (true) {
        int m, n;
        scanf("%d%d", &m, &n);
        if (m == -1 && n == -1) break;

        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &rooms[i].j, &rooms[i].f);
        sort(rooms, rooms + n);

        double ans = 0, rest = m;
        for (int i = 0; i < n; i++) {
            if (rooms[i].f < rest) {
                ans += rooms[i].j;
                rest -= rooms[i].f;
            }
            else {
                ans += rest / rooms[i].f * rooms[i].j;
                break;
            }
        }
        printf("%.3f\n", ans);
    }
}
