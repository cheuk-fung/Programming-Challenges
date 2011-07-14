/*
 *  SRC: POJ 1101
 * PROB: The Game
 * ALGO: BFS
 * DATE: Jul 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

char board[100][100];
bool visited[100][100];
int w, h;

struct Point {
    int x, y, s;

    Point(int xx = 0, int yy = 0, int ss = 0)
        : x(xx), y(yy), s(ss)
    { }
};

const int step[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

bool solve()
{
    static int n = 1;

    scanf("%d%d", &w, &h);
    if (!(w || h)) return false;

    printf("Board #%d:\n", n++);

    for (int j = 0; j <= w + 1; j++)
        board[0][j] = board[h + 1][j] = ' ';
    for (int i = 0; i <= h + 1; i++)
        board[i][0] = board[i][w + 1] = ' ';

    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            while ((board[i][j] = getchar()) == '\n') ;

    Point ps, pe;
    int cnt = 1;
    while (1 + 1 == 2) {
        scanf("%d%d%d%d", &ps.y, &ps.x, &pe.y, &pe.x);
        if (!(ps.x || ps.y || pe.x || pe.y)) break;

        memset(visited, false, sizeof(visited));

        board[pe.x][pe.y] = ' ';

        queue<Point> que;
        ps.s = pe.s = 0;
        que.push(ps);
        visited[ps.x][ps.y] = true;

        while (!que.empty()) {
            Point p = que.front();
            que.pop();

            for (int i = 0; i < 4; i++) {
                int x = p.x, y = p.y;
                while (0 <= x && x <= h + 1 && 0 <= y && y <= w + 1) {
                    x += step[i][0];
                    y += step[i][1];

                    if (board[x][y] != ' ') break;
                    if (visited[x][y]) continue;
                    
                    if (x == pe.x && y == pe.y) {
                        pe.s = p.s + 1;
                        goto WRITEANS;
                    }

                    que.push(Point(x, y, p.s + 1));
                    visited[x][y] = true;
                }
            }
        }

WRITEANS:
        printf("Pair %d: ", cnt++);
        if (pe.s) printf("%d segments.\n", pe.s);
        else puts("impossible.");

        board[pe.x][pe.y] = 'X';
    }

    putchar(10);

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}
