/*
 *  SRC: HDOJ 4433
 * PROB: locker
 * ALGO: DP
 * DATE: Oct 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Node {
    int x, y;
};
queue<Node> Q;
int f[1010][10][10], inQ[10][10];;
char S[1010], T[1010];

inline void chkmin(int &a, int b) { if (a > b) a = b; }
inline int modn(int x) { return (x % 10 + 10) % 10; }

void chkque(int p, int d, int x, int y)
{
    if (d < f[p][x][y]) {
        f[p][x][y] = d;
        if (!inQ[x][y]) {
            Q.push((Node){x, y});
            inQ[x][y] = 1;
        }
    }
}

int main()
{
    while (~scanf("%s%s", S, T)) {
        int n = strlen(S);
        for (int i = 0; i < n; i++) S[i] -= '0';
        for (int i = 0; i < n; i++) T[i] -= '0';
        memset(f, 0x3f, sizeof f);
        f[0][0][0] = 0;
        for (int i = 0; i < n; i++) {
            int j = i >= 2 ? T[i - 2] : 0;
            for (int x = 0; x < (i ? 10 : 1); x++) {
                for (int l = 0; l < 10; l++) {
                    int y1 = modn(S[i] + l), y2 = modn(S[i] - l);
                    chkmin(f[i + 1][x][y1], f[i][j][x] + l);
                    chkmin(f[i + 1][x][y2], f[i][j][x] + l);
                    chkmin(f[i + 1][x][y1], f[i][j][modn(x - l)] + l);
                    chkmin(f[i + 1][x][y2], f[i][j][modn(x + l)] + l);
                    chkmin(f[i + 1][x][y1], f[i][modn(j - l)][modn(x - l)] + l);
                    chkmin(f[i + 1][x][y2], f[i][modn(j + l)][modn(x + l)] + l);
                    if (f[i + 1][x][y1] < INF) {
                        Q.push((Node){x, y1});
                        inQ[x][y1] = 1;
                    }
                    if (f[i + 1][x][y2] < INF) {
                        Q.push((Node){x, y2});
                        inQ[x][y2] = 1;
                    }
                }
            }
            while (!Q.empty()) {
                int x = Q.front().x;
                int y = Q.front().y;
                Q.pop();
                inQ[x][y] = false;
                for (int l = 0; l < 10; l++) {
                    chkque(i + 1, f[i + 1][x][y] + l, x, modn(y + l));
                    chkque(i + 1, f[i + 1][x][y] + l, x, modn(y - l));
                    chkque(i + 1, f[i + 1][x][y] + l, modn(x + l), modn(y + l));
                    chkque(i + 1, f[i + 1][x][y] + l, modn(x - l), modn(y - l));
                }
            }
        }
        printf("%d\n", f[n][n >= 2 ? T[n - 2] : 0][T[n - 1]]);
    }

    return 0;
}

