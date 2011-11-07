/*
 *  SRC: HDOJ 3681
 * PROB: Prison Break
 * ALGO: DP
 * DATE: Nov 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

const int dir[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

struct Node {
    int x, y;
    int d;
};
Node hash[15];

int  n, m, sid;
int  final_status, node_cnt;
int  dist[15][15][15][15];
int  f[1 << 15][15];
char map[20][20];

Node bfs_q[225],
     *head, *tail;
int  vis[15][15];

void calc_dist(int sx, int sy)
{
    memset(vis, 0, sizeof(vis));

    head = tail = bfs_q;
    *tail++ = (Node){sx, sy, 0};
    vis[sx][sy] = 1;

    while (head != tail) {
        Node curr = *head++;
        for (int i = 0; i < 4; i++) {
            int x = curr.x + dir[i][0],
                y = curr.y + dir[i][1];
            if (!(0 <= x && x < n)) continue;
            if (!(0 <= y && y < m)) continue;
            if (vis[x][y] || map[x][y] == 'D') continue;

            dist[sx][sy][x][y] = curr.d + 1;
            *tail++ = (Node){x, y, curr.d + 1};
            vis[x][y] = 1;
        }
    }
}

bool check(int max_e)
{
    // int res = -1;

    memset(f, 0xff, sizeof(f));
    f[1 << sid][sid] = max_e;

    for (int s = sid, final_s = 1 << node_cnt; s < final_s; s++)
        for (int i = 0; i < node_cnt; i++) {
            if (!(s & (1 << i)) || f[s][i] == -1) continue;
            // if ((s & final_status) == final_status) res = max(res, f[s][i]);
            if ((s & final_status) == final_status) return 1;
            for (int j = 0; j < node_cnt; j++) {
                if (s & (1 << j)) continue;

                int curr_s = s | (1 << j),
                    d = dist[hash[i].x][hash[i].y][hash[j].x][hash[j].y];
                if (d < 0 || f[s][i] - d < 0) continue;

                f[curr_s][j] = max(f[curr_s][j], f[s][i] - d);
                if (map[hash[j].x][hash[j].y] == 'G') f[curr_s][j] = max_e;
            }
        }

    // return res >= 0;
    return 0;
}

int main()
{
    while (scanf("%d%d", &n, &m), n && m) {
        final_status = node_cnt = 0;
        memset(dist, 0xff, sizeof(dist));

        for (int i = 0; i < n; i++) {
            scanf("%s", map[i]);
            for (int j = 0; j < m; j++)
                switch (map[i][j]) {
                    case 'F':
                        sid = node_cnt;
                        hash[node_cnt].x = i;
                        hash[node_cnt].y = j;
                        final_status |= 1 << node_cnt++;
                        break;
                    case 'Y':
                        hash[node_cnt].x = i;
                        hash[node_cnt].y = j;
                        final_status |= 1 << node_cnt++;
                        break;
                    case 'G':
                        hash[node_cnt].x = i;
                        hash[node_cnt].y = j;
                        node_cnt++;
                }
        }

        for (int i = 0; i < node_cnt; i++) calc_dist(hash[i].x, hash[i].y);

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
