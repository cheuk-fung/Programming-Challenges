/*
 *  SRC: POJ 2688
 * PROB: Cleaning Robot
 * ALGO: BFS
 * DATE: Jul 15, 3011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using std::queue;
using std::next_permutation;

int n, m;
char map[30][30];
bool visited[30][30];

struct Point {
    int x, y;

    Point() { }
    Point(int _x, int _y)
        : x(_x), y(_y)
    { }
};

struct Node : public Point {
    int t;

    Node(int _x, int _y, int _t)
        : Point(_x, _y), t(_t)
    { }
};


const int dir[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int bfs(int bx, int by, int ex, int ey)
{
    memset(visited, false, sizeof(visited));

    queue<Node> Q;
    Q.push(Node(bx, by, 0));
    visited[bx][by] = true;

    while (!Q.empty()) {
        Node p = Q.front();
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int x = p.x + dir[i][0];
            int y = p.y + dir[i][1];

            if (0 <= x && x < n && 0 <= y && y < m) {
                if (x == ex && y == ey) return p.t + 1;

                if (!visited[x][y] && map[x][y] == '.') {
                    Q.push(Node(x, y, p.t + 1));
                    visited[x][y] = true;
                }
            }
        }
    }

    return -1;
}

int main()
{
NEXT:
    while (scanf("%d%d", &m, &n) == 2) {
        if (!(m || n)) break;

        for (int i = 0; i < n; i++) scanf("%s", map[i]);

        int bx, by, cnt = 0;
        Point dirty[30];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (map[i][j] == '*') {
                    dirty[cnt++] = Point(i, j);
                    map[i][j] = '.';
                }
                if (map[i][j] == 'o') {
                    bx = i;
                    by = j;
                    map[i][j] = '.';
                }
            }

        int dis[30];
        for (int i = 0; i < cnt; i++) {
            dis[i] = bfs(bx, by, dirty[i].x, dirty[i].y);
            if (dis[i] == -1) {
                puts("-1");
                goto NEXT;
            }
        }

        int dirDis[30][30];
        for (int i = 0; i < cnt; i++)
            for (int j = 0; j < i; j++)
                dirDis[i][j] = dirDis[j][i] = \
                    bfs(dirty[i].x, dirty[i].y, dirty[j].x, dirty[j].y);

        int per[30];
        for (int i = 0; i < cnt; i++) per[i] = i;

        int min = 0x7FFFFFFF;
        do {
            int tot = dis[per[0]];
            for (int i = 0; i + 1 < cnt; i++)
                tot += dirDis[per[i]][per[i + 1]];
            if (tot < min) min = tot;
        } while (next_permutation(per, per + cnt)) ;

        printf("%d\n", min);
    }

    return 0;
}
