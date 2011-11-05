/*
 *  SRC: HDOJ 3681
 * PROB: Prison Break
 * ALGO: Bisection + BFS
 * DATE: Nov 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int SIZE = 1500000;
const short dir[4][2] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0}
};

int n, m, final;
int hash[15][15];
char map[20][20];

struct Point {
    short x, y;
    short s, e;

    Point() { }
    Point(short _x, short _y, short _s, short _e) : x(_x), y(_y), s(_s), e(_e) { }
};
Point start;
Point bfs_q[SIZE + 10];
short f[15][15][1 << 15];

bool check(int max_e)
{
    start.e = max_e;
    memset(f, 0, sizeof(f));

    int head = 0, tail = 0;
    bfs_q[tail++] = start;
    f[start.x][start.y][0] = max_e;

    while (head != tail) {
        Point curr = bfs_q[head++ % SIZE];
        for (int i = 0; i < 4; i++) {
            short x = curr.x + dir[i][0],
                  y = curr.y + dir[i][1],
                  s = curr.s;
            if (!(0 <= x && x < n)) continue;
            if (!(0 <= y && y < m)) continue;

            if (map[x][y] == 'D') continue;

            if (map[x][y] == 'Y') s |= 1 << hash[x][y];
            if ((s & final) == final) return 1;
            if (f[x][y][s] < curr.e - 1) {
                bfs_q[tail++ % SIZE] = Point(x, y, s, curr.e - 1);
                f[x][y][s] = curr.e - 1;
            }

            if (map[x][y] == 'G') {
                if (curr.s & (1 << hash[x][y])) continue;
                s |= 1 << hash[x][y];
                if (f[x][y][s] < max_e) {
                    bfs_q[tail++ % SIZE] = Point(x, y, s, max_e);
                    f[x][y][s] = max_e;
                }
            }
        }
    }
    return 0;
}

int main()
{
    while (scanf("%d%d", &n, &m), n && m) {
        final = 0;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            scanf("%s", map[i]);
            for (int j = 0; j < m; j++)
                switch (map[i][j]) {
                    case 'F': start.x = i; start.y = j; map[i][j] = 'S'; break;
                    case 'G': hash[i][j] = cnt++; break;
                    case 'Y': final |= 1 << cnt; hash[i][j] = cnt++; break;
                }
        }

        if(final == 0) {
            puts("0");
            continue;
        }

        int l = 0, r = n * m;
        while (l < r) {
            int mid = (l + r - 1) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }

        printf("%d\n", l == n * m ? -1 : l);
    }

    return 0;
}
