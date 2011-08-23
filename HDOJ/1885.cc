/*
 *  SRC: HDOJ 1885
 * PROB: Key Task
 * ALGO: BFS
 * DATE: Aug 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */


#include <cstdio>
#include <cctype>
#include <queue>

using std::queue;

struct Node {
    int x, y, s, key;
};
Node start;
int is_exit[100][100], vis[100][100][16];

int r, c, job;
char map[100][101];

int key[256];

inline bool can_go(int x, int y)
{
    return 0 <= x && x < r && 0 <= y && y < c && map[x][y] != '#';
}

inline bool expand(queue<Node>* Q, Node v, int x, int y)
{
    if (is_exit[x][y] == job) return true;

    v.x = x;
    v.y = y;
    v.s++;

    if (map[x][y] == '.')
        if (vis[x][y][v.key] != job) {
            Q->push(v);
            vis[x][y][v.key] = job;
            return false;
        }

    if (islower(map[x][y])) {
        v.key |= 1 << key[map[x][y]];
        if (vis[x][y][v.key] != job) {
            Q->push(v);
            vis[x][y][v.key] = job;
            return false;
        }
    }

    if (v.key & (1 << key[map[x][y]]))
        if (vis[x][y][v.key] != job) {
            Q->push(v);
            vis[x][y][v.key] = job;
        }

    return false;
}

int work()
{
    for (int i = 0; i < r; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < c; j++)
            switch(map[i][j]) {
                case '*': start.x = i; start.y = j; map[i][j] = '.'; break;
                case 'X': is_exit[i][j] = job;
            }
    }

    queue<Node> Q;
    Q.push(start);
    vis[start.x][start.y][0] = job;
    while (!Q.empty()) {
        Node u = Q.front();
        Q.pop();

        if (can_go(u.x + 1, u.y))
            if (expand(&Q, u, u.x + 1, u.y)) return u.s + 1;
        if (can_go(u.x - 1, u.y))
            if (expand(&Q, u, u.x - 1, u.y)) return u.s + 1;
        if (can_go(u.x, u.y + 1))
            if (expand(&Q, u, u.x, u.y + 1)) return u.s + 1;
        if (can_go(u.x, u.y - 1))
            if (expand(&Q, u, u.x, u.y - 1)) return u.s + 1;
    }

    return -1;
}

int main()
{
    key['b'] = 0; key['B'] = 0;
    key['y'] = 1; key['Y'] = 1;
    key['r'] = 2; key['R'] = 2;
    key['g'] = 3; key['G'] = 3;

    while (scanf("%d%d", &r, &c), job++, r && c) {
        int res = work();
        if (res == -1) puts("The poor student is trapped!");
        else printf("Escape possible in %d steps.\n", res);
    }

    return 0;
}
