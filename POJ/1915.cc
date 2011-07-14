/*
 *  SRC: POJ 1915
 * PROB: Knight Moves
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

const int jump[8][2] = {
    {-2, -1},
    {-1, -2},
    {-2, 1},
    {1, -2},
    {2, -1},
    {-1, 2},
    {1, 2},
    {2, 1}
};

struct Point {
    int x, y, step;

    Point(int xx = 0, int yy = 0, int ss = 0)
        : x(xx), y(yy), step(ss)
    { }
};

bool visited[310][310];

void solve()
{
    int l;
    Point ps, pe;
    scanf("%d%d%d%d%d", &l, &ps.x, &ps.y, &pe.x, &pe.y);

    memset(visited, false, sizeof(visited));

    queue<Point> que;

    que.push(ps);
    ps.step = 0;
    visited[ps.x][ps.y] = true;

    if (pe.x ==  ps.x && pe.y == ps.y) {
        puts("0");
        return ;
    }

    while (!que.empty()) {
       Point p = que.front();
       que.pop();

       for (int i = 0; i < 8; i++) {
           int x = p.x + jump[i][0], y = p.y + jump[i][1];
           if (0 <= x && x < l && 0 <= y && y < l) {
               if (x == pe.x && y == pe.y) {
                   printf("%d\n", p.step + 1);
                   return ;
               }
               if (!visited[x][y]) {
                   que.push(Point(x, y, p.step + 1));
                   visited[x][y] = true;
               }
           }
       }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n--) solve();

    return 0;
}
