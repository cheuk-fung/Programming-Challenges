/*
 *  SRC: HDOJ 4452
 * PROB: Running Rabbits
 * ALGO: Implementation
 * DATE: Oct 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}
};

int n;
int getdir[256];

inline bool inboard(int x, int y) { return 0 < x && x <= n && 0 < y && y <= n; }

int main()
{
    getdir['N'] = 0;
    getdir['W'] = 1;
    getdir['S'] = 2;
    getdir['E'] = 3;

    while (scanf("%d", &n), n) {
        char c1, c2;
        int s1, t1;
        int s2, t2;
        scanf(" %c%d%d", &c1, &s1, &t1);
        scanf(" %c%d%d", &c2, &s2, &t2);
        int d1 = getdir[c1], d2 = getdir[c2];
        int K;
        scanf("%d", &K);
        int x1 = 1, y1 = 1;
        int x2 = n, y2 = n;
        for (int i = 0; i < K; i++) {
            if (x1 == x2 && y1 == y2) swap(d1, d2);
            else if (i > 0) {
                if (i % t1 == 0) d1 = (d1 + 1) % 4;
                if (i % t2 == 0) d2 = (d2 + 1) % 4;
            }
            for (int j = 0; j < s1; j++) {
                int xx = x1 + dir[d1][0];
                int yy = y1 + dir[d1][1];
                if (!inboard(xx, yy)) {
                    d1 = (d1 + 2) % 4;
                    xx = x1 + dir[d1][0];
                    yy = y1 + dir[d1][1];
                }
                x1 = xx;
                y1 = yy;
            }
            for (int j = 0; j < s2; j++) {
                int xx = x2 + dir[d2][0];
                int yy = y2 + dir[d2][1];
                if (!inboard(xx, yy)) {
                    d2 = (d2 + 2) % 4;
                    xx = x2 + dir[d2][0];
                    yy = y2 + dir[d2][1];
                }
                x2 = xx;
                y2 = yy;
            }
        }
        printf("%d %d\n", x1, y1);
        printf("%d %d\n", x2, y2);
    }

    return 0;
}

