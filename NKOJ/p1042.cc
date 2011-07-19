/*
 *  SRC: NKOJ p1042
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

bool visited[10][10];

bool solve()
{
    char s1[10], s2[10];
    if (scanf("%s%s", s1, s2) != 2) return false;

    Point ps, pe;
    ps.x = s1[0] - 'a';
    ps.y = s1[1] - '1';
    pe.x = s2[0] - 'a';
    pe.y = s2[1] - '1';

    memset(visited, false, sizeof(visited));

    queue<Point> que;

    que.push(ps);
    ps.step = 0;
    visited[ps.x][ps.y] = true;

    if (pe.x ==  ps.x && pe.y == ps.y) {
        printf("To get from %s to %s takes %d knight moves.\n", s1, s2, 0);
        return true;
    }

    while (!que.empty()) {
       Point p = que.front();
       que.pop();

       for (int i = 0; i < 8; i++) {
           int x = p.x + jump[i][0], y = p.y + jump[i][1];
           if (0 <= x && x < 8 && 0 <= y && y < 8) {
               if (x == pe.x && y == pe.y) {
                   printf("To get from %s to %s takes %d knight moves.\n", s1, s2, p.step + 1);
                   return true;
               }
               if (!visited[x][y]) {
                   que.push(Point(x, y, p.step + 1));
                   visited[x][y] = true;
               }
           }
       }
    }

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}

