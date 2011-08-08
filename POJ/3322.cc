/*
 *  SRC: POJ 3322
 * PROB: Bloxorz I
 * ALGO: BFS
 * DATE: Aug 07, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

const int dir[][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

struct Point {
    int x, y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};
Point dst;

struct Node {
    int mode; // 0 for single, 1 for couple
    int s;
    Point a, b;
};
Node src;

int r, c;
char map[500][501];
bool visSin[500][500];
int visCou[500][500];

bool check(const Node& v, int mode, int d = 0)
{
    if (mode)
        return map[v.a.x][v.a.y] != '#'
            && map[v.b.x][v.b.y] != '#'
            && !(visCou[v.a.x][v.a.y] & (1 << d))
            && !(visCou[v.b.x][v.b.y] & (1 << ((d + 2) % 4)));
    return map[v.a.x][v.a.y] == '.' && !visSin[v.a.x][v.a.y];
}

void expand(queue<Node>* Q, Node& v, int mode, int d = 0)
{
    v.mode = mode;
    Q->push(v);
    if (mode) {
        visCou[v.a.x][v.a.y] |= 1 << d;
        visCou[v.b.x][v.b.y] |= 1 << ((d + 2) % 4);
    }
    else visSin[v.a.x][v.a.y] = true;
}

void bfs()
{
    memset(visSin, false, sizeof(visSin));
    memset(visCou, 0, sizeof(visCou));
    
    queue<Node> Q;
    Q.push(src);
    if (src.mode) {
        for (int i = 0; i < 4; i++)
            if (src.a.x + dir[i][0] == src.b.x && src.a.y + dir[i][1] == src.b.y) {
                visCou[src.a.x][src.a.y] |= (1 << i);
                visCou[src.b.x][src.b.y] |= (1 << ((i + 2) % 4));
                break;
            }
    }
    else visSin[src.a.x][src.a.y] = true;

    while (!Q.empty()) {
        const Node u = Q.front();
        Q.pop();
        if (u.mode)
        {
            for (int i = 0; i < 4; i++)
                if (u.a.x + dir[i][0] == u.b.x && u.a.y + dir[i][1] == u.b.y) {
                    Node v;
                    v.s = u.s + 1;

                    v.a.x = u.b.x + dir[i][0],
                    v.a.y = u.b.y + dir[i][1];
                    if (v.a == dst) {
                        printf("%d\n", v.s);
                        return ;
                    }
                    if (check(v, 0))
                        expand(&Q, v, 0);

                    v.a.x = u.a.x - dir[i][0],
                    v.a.y = u.a.y - dir[i][1];
                    if (v.a == dst) {
                        printf("%d\n", v.s);
                        return ;
                    }
                    if (check(v, 0))
                        expand(&Q, v, 0);

                    int j = (i + 1) % 4;
                    v.a.x = u.a.x + dir[j][0];
                    v.a.y = u.a.y + dir[j][1];
                    v.b.x = u.b.x + dir[j][0];
                    v.b.y = u.b.y + dir[j][1];
                    if (check(v, 1, i))
                        expand(&Q, v, 1, i);

                    v.a.x = u.a.x - dir[j][0];
                    v.a.y = u.a.y - dir[j][1];
                    v.b.x = u.b.x - dir[j][0];
                    v.b.y = u.b.y - dir[j][1];
                    if (check(v, 1, i))
                        expand(&Q, v, 1, i);
                }
        }
        else {
            for (int i = 0; i < 4; i++) {
                Node v;
                v.s = u.s + 1;

                v.a.x = u.a.x + dir[i][0];
                v.a.y = u.a.y + dir[i][1];
                v.b.x = u.a.x + dir[i][0] * 2;
                v.b.y = u.a.y + dir[i][1] * 2;
                if (check(v, 1, i))
                    expand(&Q, v, 1, i);
            }
        }
    }
    puts("Impossible");
}

int main()
{
    while (scanf("%d%d", &r, &c), r || c) {
        src.mode = 0;
        for (int i = 0; i < r; i++) {
            scanf("%s", map[i]);
            for (int j = 0; j < c; j++)
                switch(map[i][j]) {
                    case '.':
                    case '#': 
                    case 'E': break;
                    case 'O': {
                                  dst.x = i;
                                  dst.y = j;
                                  map[i][j] = '.';
                                  break;
                              }
                    case 'X': {
                                  Point* p = &src.a;
                                  if (src.mode) p = &src.b;
                                  p->x = i;
                                  p->y = j;
                                  src.mode++;
                                  map[i][j] = '.';
                              }
                }
        }
        src.mode--;

        bfs();
    }

    return 0;
}
