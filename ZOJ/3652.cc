/*
 *  SRC: ZOJ 3652
 * PROB: Maze
 * ALGO: Dijkstra
 * DATE: Sep 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MAXSIZE = 1000000;
const int dir[4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

int n, m, l, k;
int sx, sy, tx, ty;
int f[MAXSIZE];
int mat[55][55];
pii monster[5];
int J0, J1, J2;

struct Status {
    int turns;
    int s;

    Status(int _turns, int _s) : turns(_turns), s(_s) { }
    bool operator<(const Status &o) const { return turns > o.turns; }
};

inline int encode(int x, int y, int s, int r)
{
    return x * J2 + y * J1 + s * J0 + r;
}

int dijkstra()
{
    int res = INF;

    memset(f, 0x3f, sizeof f);
    priority_queue<Status> Q;
    Q.push(Status(0, encode(sx, sy, 0, 0)));
    f[encode(sx, sy, 0, 0)] = 0;
    while (!Q.empty()) {
        int turns = Q.top().turns;
        int u = Q.top().s;
        Q.pop();
        if (turns > f[u]) continue;

        int x = u / J2, y = u % J2 / J1, s = u % J1 / J0, r = u % J0;
        if (r == 0) {
            turns++;
            r = l;
        }
        for (int d = 0; d < 4; d++) {
            int xx = x + dir[d][0];
            int yy = y + dir[d][1];
            int ss = s;
            int rr = r;
            if (!(0 <= xx && xx < n) || !(0 <= yy && yy < m) || mat[xx][yy] == -1) continue;
            if (xx == tx && yy == ty) {
                res = min(res, turns);
            }
            if (mat[xx][yy] != 0 && (s & mat[xx][yy]) == 0) rr = 0;
            else rr--;

            for (int i = 0; i < k; i++) {
                if (xx == monster[i].first && yy == monster[i].second) {
                    ss |= 1 << i;
                    break;
                }
            }

            int code = encode(xx, yy, ss, rr);
            if (turns < f[code]) {
                f[code] = turns;
                Q.push(Status(turns, code));
            }
        }
    }
    return res;
}

int main()
{
    while (~scanf("%d%d%d", &n, &m, &l)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &mat[i][j]);
                if (mat[i][j] > 0) mat[i][j] = 1 << (mat[i][j] - 1);
            }
        }

        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d%d", &monster[i].first, &monster[i].second);
            monster[i].first--; monster[i].second--;
        }

        scanf("%d%d", &sx, &sy);
        scanf("%d%d", &tx, &ty);
        sx--; sy--;
        tx--; ty--;

        J0 = l;
        J1 = J0 * (1 << k);
        J2 = J1 * m;

        int r = dijkstra();
        if (r == INF) {
            puts("We need God's help!");
        } else {
            printf("%d\n", r);
        }
    }

    return 0;
}

