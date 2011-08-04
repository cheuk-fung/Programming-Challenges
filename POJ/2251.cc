/*
 *  SRC: POJ 2251
 * PROB: Dungeon Master
 * ALGO: BFS
 * DATE: Aug 04, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

struct Node {
    int x, y, z, t;

    Node() { }
    Node(int _x, int _y, int _z, int _t) : x(_x), y(_y), z(_z), t(_t) { }

    bool operator==(Node& other)
    {
        return x == other.x && y == other.y && z == other.z;
    }
} st, ed;

const int dir[6][3] = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1}
};

int CASE;
int l, r, c;
char map[31][31][31];
int vis[31][31][31];

void bfs()
{
    queue<Node> Q;
    Q.push(st);
    vis[st.x][st.y][st.z] = ++CASE;

    while (!Q.empty()) {
        Node u = Q.front();
        Q.pop();

        for (int i = 0; i < 6; i++) {
            Node v(u.x + dir[i][0], u.y + dir[i][1], u.z + dir[i][2], u.t + 1);
            if (v == ed) {
                printf("Escaped in %d minute(s).\n", u.t + 1);
                return ;
            }

            if (!(0 <= v.x && v.x < l)) continue;
            if (!(0 <= v.y && v.y < r)) continue;
            if (!(0 <= v.z && v.z < c)) continue;
            if (vis[v.x][v.y][v.z] == CASE) continue;
            if (map[v.x][v.y][v.z] == '#') continue;

            Q.push(v);
            vis[v.x][v.y][v.z] = CASE;
        }
    }

    puts("Trapped!");
}

int main()
{
    while (scanf("%d%d%d", &l, &r, &c), l || r || c) {
        for (int i = 0; i < l; i++)
            for (int j = 0; j < r; j++) {
                scanf("%s", map[i][j]);
                for (int k = 0; k < c; k++) {
                    if (map[i][j][k] == 'S')
                        st = Node(i, j, k, 0);
                    else if (map[i][j][k] == 'E')
                        ed = Node(i, j, k, 0);
                }
            }

        if (st == ed) puts("Escaped in 0 minute(s).");
        else bfs();
    }

    return 0;
}
