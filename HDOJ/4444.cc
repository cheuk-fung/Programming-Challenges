/*
 *  SRC: HDOJ 4444
 * PROB: Walk
 * ALGO: SPFA
 * DATE: Oct 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int dir[4][2] = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}
};

int xall[500], yall[500];
int xid[500], yid[500];
int mat[500][500];
int dist[500][500][4], inQ[500][500][4];

struct Rect {
    int x1, y1, x2, y2;
    int x[4], y[4];
} rect[100];

int main()
{
    int x1, y1, x2, y2;
    while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2), x1 || y1 || x2 || y2) {
        int n;
        scanf("%d", &n);

        int xcnt = 0, ycnt = 0;
        xall[xcnt++] = x1; xall[xcnt++] = x2;
        yall[ycnt++] = y1; yall[ycnt++] = y2;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
            if (rect[i].x1 > rect[i].x2) swap(rect[i].x1, rect[i].x2);
            if (rect[i].y1 > rect[i].y2) swap(rect[i].y1, rect[i].y2);
            xall[xcnt++] = rect[i].x1;
            xall[xcnt++] = rect[i].x2;
            yall[ycnt++] = rect[i].y1;
            yall[ycnt++] = rect[i].y2;
        }
        sort(xall, xall + xcnt);
        sort(yall, yall + ycnt);
        xcnt = unique(xall, xall + xcnt) - xall;
        ycnt = unique(yall, yall + ycnt) - yall;
        int xmax = 10;
        for (int i = 0; i < xcnt; i++) {
            xmax += 2;
            xid[i] = xmax;
        }
        xmax += 10;

        int ymax = 10;
        for (int i = 0; i < ycnt; i++) {
            ymax += 2;
            yid[i] = ymax;
        }
        ymax += 10;

        memset(mat, 0, sizeof mat);
        for (int i = 0; i < n; i++) {
            rect[i].x1 = xid[lower_bound(xall, xall + xcnt, rect[i].x1) - xall];
            rect[i].x2 = xid[lower_bound(xall, xall + xcnt, rect[i].x2) - xall];
            rect[i].y1 = yid[lower_bound(yall, yall + ycnt, rect[i].y1) - yall];
            rect[i].y2 = yid[lower_bound(yall, yall + ycnt, rect[i].y2) - yall];
            int rx1 = rect[i].x1;
            int rx2 = rect[i].x2;
            int ry1 = rect[i].y1;
            int ry2 = rect[i].y2;
            for (int k = rx1 + 1; k < rx2; k++) {
                for (int j = ry1 + 1; j < ry2; j++) {
                    mat[k][j] = 1;
                }
            }
            rect[i].x[0] = rx1; rect[i].y[0] = ry1;
            rect[i].x[1] = rx2; rect[i].y[1] = ry2;
            rect[i].x[2] = rx1; rect[i].y[2] = ry2;
            rect[i].x[3] = rx2; rect[i].y[3] = ry1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int k = 0; k < 4; k++) {
                    if ((rect[i].x[k] == rect[j].x1 || rect[i].x[k] == rect[j].x2) && rect[j].y1 <= rect[i].y[k] && rect[i].y[k] <= rect[j].y2) {
                        mat[rect[i].x[k]][rect[i].y[k]] = 1;
                    }
                    if ((rect[i].y[k] == rect[j].y1 || rect[i].y[k] == rect[j].y2) && rect[j].x1 <= rect[i].x[k] && rect[i].x[k] <= rect[j].x2) {
                        mat[rect[i].x[k]][rect[i].y[k]] = 1;
                    }
                }
            }
        }

        x1 = xid[lower_bound(xall, xall + xcnt, x1) - xall];
        x2 = xid[lower_bound(xall, xall + xcnt, x2) - xall];
        y1 = yid[lower_bound(yall, yall + ycnt, y1) - yall];
        y2 = yid[lower_bound(yall, yall + ycnt, y2) - yall];

        queue<int> Q;
        memset(dist, 0x3f, sizeof dist);
        for (int d = 0; d < 4; d++) {
            Q.push(x1);
            Q.push(y1);
            Q.push(d);
            dist[x1][y1][d] = 0;
            inQ[x1][y1][d] = true;
        }
        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            int y = Q.front(); Q.pop();
            int d = Q.front(); Q.pop();
            inQ[x][y][d] = false;
            for (int i = 0; i < 4; i++) {
                int xx = x + dir[i][0];
                int yy = y + dir[i][1];
                int delta = i != d;
                if (!(0 <= xx && xx < xmax && 0 <= yy && yy < ymax)) continue;
                if (mat[xx][yy]) continue;
                if (dist[x][y][d] + delta < dist[xx][yy][i]) {
                    dist[xx][yy][i] = dist[x][y][d] + delta;
                    if (!inQ[xx][yy][i]) {
                        Q.push(xx);
                        Q.push(yy);
                        Q.push(i);
                        inQ[xx][yy][i] = true;
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < 4; i++) {
            ans = min(dist[x2][y2][i], ans);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }

    return 0;
}

