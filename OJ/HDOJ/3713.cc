/*
 *  SRC: HDOJ 3713
 * PROB: Double Maze
 * ALGO: BFS
 * DATE: Oct 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>

using std::string;

// const int dir[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
// const char way[4] = { 'L', 'D', 'R', 'U' };
const int  dir[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };
const char way[4]    = { 'D', 'L', 'R', 'U' };
const int  wall[4]   = { 2, 1, 4, 8 };

int map_1[6][6], map_2[6][6];

struct Status {
    int x1, y1,
        x2, y2;
    int step;
    string route;

    bool operator ==(const Status &other)
    {
        return x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2;
    }
};
Status bfs_q[1000000], final;
int vis[6][6][6][6];

void bfs()
{
    memset(vis, 0, sizeof(vis));

    Status *q_head = bfs_q,
           *q_tail = bfs_q;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            if (map_1[i][j] & 32) {
                q_tail->x1 = i;
                q_tail->y1 = j;
            }
            if (map_2[i][j] & 32) {
                q_tail->x2 = i;
                q_tail->y2 = j;
            }
            if (map_1[i][j] & 64) {
                final.x1 = i;
                final.y1 = j;
            }
            if (map_2[i][j] & 64) {
                final.x2 = i;
                final.y2 = j;
            }
        }
    if (*q_tail == final) {
        putchar(10);
        return ;
    }

    vis[q_tail->x1][q_tail->y1][q_tail->x2][q_tail->y2] = 1;
    q_tail->step = 0;
    q_tail->route = "";
    q_tail++;

    while (q_head != q_tail) {
        Status curr = *q_head++;
        int x1 = curr.x1, y1 = curr.y1,
            x2 = curr.x2, y2 = curr.y2;
        for (int i = 0; i < 4; i++) {
            int xx1 = x1, yy1 = y1,
                xx2 = x2, yy2 = y2;
            if (!(map_1[x1][y1] & wall[i])) xx1 += dir[i][0], yy1 += dir[i][1];
            if (!(map_2[x2][y2] & wall[i])) xx2 += dir[i][0], yy2 += dir[i][1];
            if (!(0 <= xx1 && xx1 < 6)) continue;
            if (!(0 <= yy1 && yy1 < 6)) continue;
            if (!(0 <= xx2 && xx2 < 6)) continue;
            if (!(0 <= yy2 && yy2 < 6)) continue;
            if (!(map_1[xx1][yy1] & 16)) continue;
            if (!(map_2[xx2][yy2] & 16)) continue;
            if (vis[xx1][yy1][xx2][yy2]) continue;

            vis[xx1][yy1][xx2][yy2] = 1;
            q_tail->x1 = xx1;
            q_tail->y1 = yy1;
            q_tail->x2 = xx2;
            q_tail->y2 = yy2;
            q_tail->step = curr.step + 1;
            q_tail->route = curr.route + way[i];
            if (*q_tail == final) {
                printf("%s\n", q_tail->route.c_str());
                return ;
            }
            q_tail++;
        }
    }

    puts("-1");
}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            scanf("%d", &map_1[i][j]);

    for (int t = 1; t < n; t++) {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                scanf("%d", &map_2[i][j]);

        bfs();

        memcpy(map_1, map_2, sizeof(map_1));
    }

    return 0;
}
