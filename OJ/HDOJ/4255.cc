/*
 *  SRC: HDOJ 4255
 * PROB: A Famous Grid
 * ALGO: Bidirectional BFS
 * DATE: Jul 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAXN = 10000010;

int mat[1002][1002];
int pos[MAXN];
bool is_prm[MAXN];
int prm[MAXN];

int timestamp = 0;
int vis[MAXN];
int len[MAXN], que1[MAXN], que2[MAXN];

int dir[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int get_prime(int n, int *p, bool *b)
{
    int cnt = 0;
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return cnt;
}

void generate()
{
    for (int i = 0; i < 1002; i++) {
        mat[0][i] = mat[1001][i] = mat[i][0] = mat[i][1001] = -1;
    }

    int x = 1, y = 1, d = 0;
    for (int i = 1000 * 1000; i > 0; i--) {
        mat[x][y] = i;
        pos[i] = x * 10000 + y;

        int xx = x + dir[d][0];
        int yy = y + dir[d][1];
        if (mat[xx][yy]) {
            d = (d + 1) % 4;
            xx = x + dir[d][0];
            yy = y + dir[d][1];
        }
        x = xx;
        y = yy;
    }
}

int expand(int *que, int *head, int *tail, int stamp)
{
    int u = que[(*head)++];
    int x = pos[u] / 10000, y = pos[u] % 10000;
    for (int i = 0; i < 4; i++) {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        int v = mat[xx][yy];

        if (v == -1 || is_prm[v] || vis[v] == stamp) continue;
        if (vis[v] == (stamp ^ 1)) {
            return len[u] + len[v] + 1;
        }
        vis[v] = stamp;
        len[v] = len[u] + 1;
        que[(*tail)++] = v;
    }

    return -1;
}

int bfs(int x, int y)
{
    if (x == y) return 0;

    que1[0] = x;
    que2[0] = y;
    len[x] = len[y] = 0;
    vis[x] = timestamp;
    vis[y] = timestamp ^ 1;

    int head1 = 0, tail1 = 1;
    int head2 = 0, tail2 = 1;
    while (head1 < tail1 && head2 < tail2) {
        if (tail1 - head1 <= tail2 - head2) {
            int r = expand(que1, &head1, &tail1, timestamp);
            if (r != -1) return r;
        } else {
            int r = expand(que2, &head2, &tail2, timestamp ^ 1);
            if (r != -1) return r;
        }
    }

    return -1;
}

int main()
{
    get_prime(MAXN, prm, is_prm);
    generate();

    int task = 1;
    int x, y;
    while (~scanf("%d%d", &x, &y)) {
        printf("Case %d: ", task++);
        timestamp += 2;
        int ans = bfs(x, y);
        if (ans != -1) printf("%d\n", ans);
        else puts("impossible");
    }

    return 0;
}

