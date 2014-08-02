/*
 *  SRC: POJ 2225
 * PROB: Asteroids!
 * ALGO: BFS
 * DATE: Aug 01, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>
#include <cstring>

using std::queue;

const int dir[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1}
};

struct Point {
    int x, y, z, s;

    Point(int _x, int _y, int _z, int _s) : x(_x), y(_y), z(_z), s(_s) { }
};

char map[10][10][11];
bool vis[10][10][10];

int main()
{
    int n;
    while (scanf("%*s%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%s", map[i][j]);

        int sx, sy, sz;
        scanf("%d%d%d", &sz, &sy, &sx);
        int ex, ey, ez;
        scanf("%d%d%d", &ez, &ey, &ex);

        scanf("%*s");

        if (sx == ex && sy == ey && sz == ez) {
            printf("%d 0\n", n);
            continue;
        }

        memset(vis, false, sizeof(vis));
        queue<Point> Q;
        Q.push(Point(sx, sy, sz, 0));
        vis[sx][sy][sz] = true;
        while (!Q.empty()) {
            Point u = Q.front();
            Q.pop();

            for (int i = 0; i < 6; i++) {
                int x = u.x + dir[i][0],
                    y = u.y + dir[i][1],
                    z = u.z + dir[i][2];
                if (!(0 <= x && x < n)) continue;
                if (!(0 <= y && y < n)) continue;
                if (!(0 <= z && z < n)) continue;
                if (!vis[x][y][z] && map[x][y][z] == 'O') {
                    if (x == ex && y == ey && z == ez) {
                        printf("%d %d\n", n, u.s + 1);
                        goto NEXT;
                    }
                    Q.push(Point(x, y, z, u.s + 1));
                    vis[x][y][z] = true;
                }
            }
        }
        puts("NO ROUTE");
NEXT:;
    }

    return 0;
}
