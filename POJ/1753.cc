/*
 *  SRC: POJ 1753
 * PROB: Flip Game
 * ALGO: BFS
 * DATE: May 9, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

char map[4][4];
bool visited[(2 << 15) + 10];
int step[(2 << 15) + 10];

queue<int> Q;

int encode()
{
    int res = 0;
    for (int i = 3; i >= 0; i--)
        for (int j = 3; j >= 0; j--) {
            if (map[i][j] == 'b') res <<= 1;
            else res = (res << 1) + 1;
        }

    return res;
}

int flip(int u, int m, int n)
{
    int v = u ^ (1 << (m * 4 + n));
    if (m > 0) v ^= 1 << ((m - 1) * 4 + n);
    if (m < 3) v ^= 1 << ((m + 1) * 4 + n);
    if (n > 0) v ^= 1 << (m * 4 + n - 1);
    if (n < 3) v ^= 1 << (m * 4 + n + 1);

    return v;
}

void decode(int v)
{
    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) putchar(10);
        if (v & 1) putchar('w');
        else putchar('b');
        v >>= 1;
    }

    getchar();
}

bool BFS()
{
    int init = encode();
    if (init == 0 || init == (2 << 15) - 1) {
        printf("0\n");
        return true;
    }
    Q.push(init);
    visited[init] = true;
    step[init] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                int v = flip(u, i, j);
                if (v == 0 || v == (2 << 15) - 1) {
                    printf("%d\n", step[u] + 1);
                    return true;
                }
                if (!visited[v]) {
                    Q.push(v);
                    visited[v] = true;
                    step[v] = step[u] + 1;
                    // decode(v);
                }
            }
    }

    return false;
}

int main()
{
    for (int i = 0; i < 4; i++) scanf("%s", map[i]);

    if (!BFS()) puts("Impossible");

    return 0;
}

