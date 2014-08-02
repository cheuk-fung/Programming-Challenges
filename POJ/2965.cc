/*
 *  SRC: POJ 2965
 * PROB: The Pilots Brothers' refrigerator
 * ALGO: BFS
 * DATE: May 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

const int maxn = (1 << 16) + 10;

struct Point {
    int x, y;

    Point(int xx = 0, int yy = 0) { x = xx; y = yy; }
};

queue<int> Q;
bool visited[maxn];
int step[maxn], fa[maxn];
Point pos[maxn];

char map[4][4];

int encode()
{
    int res = 0;
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--) {
            if (map[i][j] == '+') res = (res << 1) + 1;
            else res <<= 1;
        }

    return res;
}

int change(int u, int x, int y)
{
    int v = u ^ (1 << (x * 4 + y));
    for (int j = 0; j < 4; j++) v ^= 1 << (x * 4 + j);
    for (int i = 0; i < 4; i++) v ^= 1 << (i * 4 + y);

    return v;
}

void decode(int v)
{
    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) putchar(10);
        if (v & 1) putchar('+');
        else putchar('-');
        v >>= 1;
    }

    getchar();
}

void printPoint(int v)
{
    if (fa[v] != -1) {
        printPoint(fa[v]);
        printf("%d %d\n", pos[v].x, pos[v].y);
    }
}

void BFS()
{
    int u = encode();
    Q.push(u);
    visited[u] = true;
    step[u] = 0;
    fa[u] = -1;
    pos[u] = Point(0, 0);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                int v = change(u, i, j);
                // decode(v);
                if (!visited[v]) {
                    Q.push(v);
                    step[v] = step[u] + 1;
                    fa[v] = u;
                    pos[v] = Point(i + 1, j + 1);
                    visited[v] = true;
                    if (v == 0) {
                        printf("%d\n", step[v]);
                        printPoint(v);
                        return ;
                    }
                }
            }
    }
}

int main()
{
    for (int i = 0; i < 4; i++) scanf("%s", map[i]);

    BFS();

    return 0;
}

