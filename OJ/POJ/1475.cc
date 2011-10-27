/*
 *  SRC: POJ 1475
 * PROB: Pushing Boxes
 * ALGO: BFS + DFS
 * DATE: Aug 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int dir[][2] = {
    {1, 0},  // on the south of the box, but push it to the north
    {0, -1}, // west, east
    {-1, 0}, // north, south
    {0, 1}   // east, west
};

struct Point {
    int x, y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const
    {
        return !(*this == other);
    }
};
Point st, ed;

struct dfsNode {
    Point box, peo;
    int dir;
};
dfsNode route[400], ansRoute[400];

struct bfsNode {
    Point p;
    bfsNode* fa;
    int dir;
};
bfsNode que[400];

int r, c, CASE, ans;
bool vis[20][20];
int push[20][20][20][20];
char map[20][21];


bool check(const Point& p)
{
    if (!(0 <= p.x && p.x < r)) return false;
    if (!(0 <= p.y && p.y < c)) return false;
    if (map[p.x][p.y] == '#') return false;
    if (vis[p.x][p.y]) return false;

    return true;
}

void floodfill(int bx, int by, int px, int py, int d)
{
    Point t;
    t.x = px;
    t.y = py;
    if (!check(t)) return ;

    push[bx][by][px][py] |= d;
    vis[px][py] = true;

    for (int i = 0; i < 4; i++)
        floodfill(bx, by, px + dir[i][0], py + dir[i][1], d);
}

void init()
{
    memset(push, 0, sizeof(push));
    ans = 0x3fffffff;

    for (int i = 0; i < r; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < c; j++)
            switch(map[i][j]) {
                case '.':
                case '#': break;
                case 'S': route->peo.x = i;
                          route->peo.y = j;
                          break;
                case 'B': route->box.x = i;
                          route->box.y = j;
                          break;
                case 'T': ed.x = i;
                          ed.y = j;
            }
    }

    for (int bx = 0; bx < r; bx++)
        for (int by = 0; by < c; by++)
            for (int i = 0; i < 4; i++) {
                if (map[bx][by] == '#') continue;
                memset(vis, false, sizeof(vis));
                vis[bx][by] = true;
                floodfill(bx, by, bx + dir[i][0], by + dir[i][1], 1 << i);
            }

    memset(vis, false, sizeof(vis));
    vis[route->box.x][route->box.y] = true;
}

inline int dist(const Point& p)
{
    return abs(ed.x - p.x) + abs(ed.y - p.y);
}

inline dfsNode* expand(dfsNode* u, int d)
{
    dfsNode*v = u + 1;
    v->box.x = u->box.x - dir[d][0];
    v->box.y = u->box.y - dir[d][1];
    v->peo.x = u->box.x + dir[d][0];
    v->peo.y = u->box.y + dir[d][1];
    v->dir = d;
    return v;
}

void dfs(dfsNode* u, int curr)
{
    if (curr + dist(u->box) >= ans) return ;
    if (u->box == ed) {
        ans = curr;
        for (int i = 0; i < curr; i++)
            ansRoute[i] = route[i];
        return ;
    }

    vis[u->box.x][u->box.y] = true;
    for (int i = 0; i < 4; i++)
        if (push[u->box.x][u->box.y][u->peo.x][u->peo.y] & (1 << i)) {
            dfsNode* v = expand(u, i);
            if (check(v->box))
                dfs(v, curr + 1);
        }
    vis[u->box.x][u->box.y] = false;
}

void printPeo(bfsNode* p)
{
    if (!p->fa) return ;
    printPeo(p->fa);
    switch(p->dir) {
        case 0: putchar('s'); break;
        case 1: putchar('w'); break;
        case 2: putchar('n'); break;
        case 3: putchar('e'); break;
    }
}

void bfs()
{
    memset(vis, false, sizeof(vis));
    bfsNode* head = que;
    bfsNode* tail = que;
    
    tail->p = st;
    tail->fa = 0;
    tail->dir = -1;
    vis[st.x][st.y] = true;
    tail++;

    while (head != tail) {
        bfsNode* u = head++;
        for (int i = 0; i < 4; i++) {
            bfsNode* v = tail;
            v->p.x = u->p.x + dir[i][0];
            v->p.y = u->p.y + dir[i][1];
            v->fa = u;
            v->dir = i;
            if (v->p == ed) {
                printPeo(tail);
                return ;
            }
            if (check(v->p)) {
                vis[v->p.x][v->p.y] = true;
                tail++;
            }
        }
    }
}

void printRoute()
{
    dfsNode* u = ansRoute;
    for (int i = 1; i < ans; i++) {
        st = u[i - 1].peo;
        if (i != 1) {
            int d = u[i - 1].dir;
            st.x -= dir[d][0];
            st.y -= dir[d][1];
        }
        ed = u[i].peo;
        if (st != ed) {
            map[u[i - 1].box.x][u[i - 1].box.y] = '#';
            bfs();
            map[u[i - 1].box.x][u[i - 1].box.y] = '.';
        }

        if (u[i - 1].box.x + 1 == u[i].box.x) putchar('S');
        else if (u[i - 1].box.y - 1 == u[i].box.y) putchar('W');
        else if (u[i - 1].box.x - 1 == u[i].box.x) putchar('N');
        else if (u[i - 1].box.y + 1 == u[i].box.y) putchar('E');
    }
    putchar(10);
}

int main()
{
    while (scanf("%d%d", &r, &c), r || c) {
        init();
        dfs(route, 1);
        printf("Maze #%d\n", ++CASE);
        if (ans < 0x3fffffff) printRoute();
        else puts("Impossible.");
        putchar(10);
    }
    return 0;
}
