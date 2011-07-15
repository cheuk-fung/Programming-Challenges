/*
 *  SRC: POJ 1376
 * PROB: Robot
 * ALGO: BFS
 * DATE: Jul 15, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

int T, n, m;
int bx, by, ex, ey, bd;
char sbd[10];
int map[100][100];
int visited[100][100][4];

const int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}
};

struct Node {
    int x, y, d, t;

    Node(int _x, int _y, int _d, int _t)
        : x(_x), y(_y), d(_d), t(_t)
    { }
};

int bfs()
{
    queue<Node> Q;
    Q.push(Node(bx, by, bd, 0));
    visited[bx][by][bd] = T;

    while (!Q.empty()) {
        Node p = Q.front();
        Q.pop();

        for (int i = 1; i <= 3; i++) {
            int x = p.x + dir[p.d][0] * i;
            int y = p.y + dir[p.d][1] * i;

            if (x == ex && y == ey) return p.t + 1;

            if (0 < x && x < n && 0 < y && y < m) {
                if (map[x][y] == T) break;
                if (visited[x][y][p.d] != T) {
                    Q.push(Node(x, y, p.d, p.t + 1));
                    visited[x][y][p.d] = T;
                }
            }
        }

        for (int i = 1; i <= 3; i += 2) {
            int d = (p.d + i) % 4;
            if (visited[p.x][p.y][d] != T) {
                Q.push(Node(p.x, p.y, d, p.t + 1));
                visited[p.x][p.y][d] = T;
            }
        }
    }

    return -1;
}

int main()
{
    while (scanf("%d%d", &n, &m) == 2) {
        if (!(n || m)) break;

        T++;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int t;
                scanf("%d", &t);
                if (t == 1)
                    map[i][j] = map[i + 1][j] = map[i][j + 1] = map[i + 1][j + 1] = T;
            }

        scanf("%d%d%d%d%s", &bx, &by, &ex, &ey, sbd);

        if (bx == ex && by == ey) {
            puts("0");
            continue;
        }

        if (map[bx][by] == T || map[ex][ey] == T) {
            puts("-1");
            continue;
        }

        switch(sbd[0]) {
            case 'n': bd = 0; break;
            case 'w': bd = 1; break;
            case 's': bd = 2; break;
            case 'e': bd = 3; break;
        }

        printf("%d\n", bfs());
    }

    return 0;
}
