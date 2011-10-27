/*
 *  SRC: POJ 1606
 * PROB: Jugs
 * ALGO: BFS
 * DATE: Aug 01, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

struct Node {
    int a, b, fa, act;
} q[1000001];

int vis[1001][1001], open, closed;
int ca, cb, n, CASE;

void printAns(int p)
{
    if (q[p].fa == -1) return ;
    printAns(q[p].fa);
    switch(q[p].act) {
        case 1: puts("fill A"); break;
        case 2: puts("fill B"); break;
        case 3: puts("empty A"); break;
        case 4: puts("empty B"); break;
        case 5: puts("pour A B"); break;
        case 6: puts("pour B A");
    }
}

inline bool pushQue(int a, int b, int act)
{
    q[closed].a = a;
    q[closed].b = b;
    q[closed].fa = open;
    q[closed].act = act;
    vis[a][b] = CASE;

    if (b == n) {
        printAns(closed);
        return true;
    }

    closed++;

    return false;
}


void bfs()
{
    open = closed = 0;
    q[0].a = 0;
    q[0].b = 0;
    q[0].fa = -1;
    vis[0][0] = ++CASE;
    closed++;

    while (open < closed) {
        Node u = q[open];

        if (vis[ca][u.b] != CASE) // fill A
            if (pushQue(ca, u.b, 1)) return ;

        if (vis[u.a][cb] != CASE) // fill B
            if (pushQue(u.a, cb, 2)) return ;

        if (vis[0][u.b] != CASE) // empty A
            if (pushQue(0, u.b, 3)) return ;

        if (vis[u.a][0] != CASE) // empty B
            if (pushQue(u.a, 0, 4)) return ;

        if (u.a && u.b < cb) { // pour A B (pour A into B)
            int a, b;
            if (u.a + u.b < cb) {
                a = 0;
                b = u.a + u.b;
            }
            else {
                a = u.a + u.b - cb;
                b = cb;
            }
            if (vis[a][b] != CASE)
                if (pushQue(a, b, 5)) return ;
        }

        if (u.a < ca && u.b) { // pour B A
            int a, b;
            if (u.a + u.b < ca) {
                a = u.a + u.b;
                b = 0;
            }
            else {
                a = ca;
                b = u.a + u.b - ca;
            }
            if (vis[a][b] != CASE)
                if (pushQue(a, b, 6)) return ;
        }

        open++;
    }
}

int main()
{
    while (scanf("%d%d%d", &ca, &cb, &n) == 3) {
        bfs();
        puts("success");
    }

    return 0;
}
