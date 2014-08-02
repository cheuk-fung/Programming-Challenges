/*
 *  SRC: POJ 1324
 * PROB: Holedox Moving
 * ALGO: BFS
 * DATE: Aug 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>

using std::queue;

unsigned short dir[4][2] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

struct Node {
    unsigned short x, y, status, step;

    bool operator==(const Node& other) const
    {
        return x == other.x && y == other.y;
    }
} st, ed;

int n, m, l;
unsigned char CASE;
unsigned short LIM;
unsigned char vis[21][21][1 << 15];
bool map[21][21];
Node snake[8];

unsigned short encode()
{
    unsigned short res = 0;
    for (int i = 1; i < l; i++) {
        // the ith block lies on the *north* of the (i-1)th, encoded to 00
        if (snake[i].x == snake[i - 1].x - 1 && snake[i].y == snake[i - 1].y)
            continue;
        // east, 01
        if (snake[i].x == snake[i - 1].x && snake[i].y == snake[i - 1].y + 1)
            res |= 1 << ((i - 1) * 2);
        // south, 10
        if (snake[i].x == snake[i - 1].x + 1 && snake[i].y == snake[i - 1].y)
            res |= 2 << ((i - 1) * 2);
        // west, 11
        if (snake[i].x == snake[i - 1].x && snake[i].y == snake[i - 1].y - 1)
            res |= 3 << ((i - 1) * 2);
    }
    return res;
}

void decode(const Node& u)
{
    unsigned short x = u.x, y = u.y, code = u.status;
    snake[0].x = x;
    snake[0].y = y;
    int cnt = 0;
    while (cnt < l)  {
        cnt++;
        int delta = code & 3;
        code >>= 2;
        switch(delta) {
            case 0: snake[cnt].x = snake[cnt - 1].x - 1;
                    snake[cnt].y = snake[cnt - 1].y;
                    break;
            case 1: snake[cnt].x = snake[cnt - 1].x;
                    snake[cnt].y = snake[cnt - 1].y + 1;
                    break;
            case 2: snake[cnt].x = snake[cnt - 1].x + 1;
                    snake[cnt].y = snake[cnt - 1].y;
                    break;
            case 3: snake[cnt].x = snake[cnt - 1].x;
                    snake[cnt].y = snake[cnt - 1].y - 1;
        }
    }
}

unsigned short bfs()
{
    queue<Node> Q;
    Q.push(st);
    vis[st.x][st.y][st.status] = CASE;

    while (!Q.empty()) {
        Node u = Q.front();
        Q.pop();
        decode(u);
        for (int i = 0; i < l; i++)
            map[snake[i].x][snake[i].y] = true;
        for (int i = 0; i < 4; i++) {
            Node v = snake[0];
            v.x += dir[i][0];
            v.y += dir[i][1];
            v.status = ((u.status << 2) + i) & LIM;
            v.step = u.step + 1;

            if (v == ed) return v.step;

            if (!(0 < v.x && v.x <= n)) continue;
            if (!(0 < v.y && v.y <= m)) continue;
            if (map[v.x][v.y]) continue;
            if (vis[v.x][v.y][v.status] == CASE) continue;

            Q.push(v);
            vis[v.x][v.y][v.status] = CASE;
        }
        for (int i = 0; i < l; i++)
            map[snake[i].x][snake[i].y] = false;
    }

    return -1;
}

int main()
{
    ed.x = ed.y = 1;

    while (scanf("%d%d%d", &n, &m, &l), n || m || l) {
        CASE++;
        LIM = (1 << ((l - 1) * 2)) - 1;

        for (int i = 0; i < l; i++)
            scanf("%hd%hd", &snake[i].x, &snake[i].y);

        memset(map, false, sizeof(map));
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            map[x][y] = true;
        }

        st = snake[0];
        st.status = encode();
        st.step = 0;
        printf("Case %d: %hd\n", (int)CASE, st == ed ? 0 : bfs());
    }

    return 0;
}
