#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <cctype>

using namespace std;

typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

string mat[15];
int f[15][15][1 << 16];
pii snake[9];

int main()
{
    int n, m;
    cin >> n >> m;
    int sl = 0;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
        for (int j = 0; j < m; j++) {
            if (isdigit(mat[i][j])) {
                snake[mat[i][j] - '1'] = pii(i, j);
                sl = max(sl, mat[i][j] - '0');
            }
        }
    }
    int s = 0;
    for (int i = 1; i < sl; i++) {
        for (int d = 0; d < 4; d++) {
            if (snake[i - 1].first + dir[d][0] == snake[i].first && snake[i - 1].second + dir[d][1] == snake[i].second) {
                s = s << 2 | d;
                break;
            }
        }
    }
    queue<int> Q;
    memset(f, 0x3f, sizeof f);
    f[snake[0].first][snake[0].second][s] = 0;
    Q.push((snake[0].first << 20) + (snake[0].second << 16) + s);
    while (!Q.empty()) {
        int x = Q.front() >> 20, y = Q.front() >> 16 & 0x0f, s = Q.front() & 0xffff;
        Q.pop();

        int xx = x, yy = y;
        for (int i = 1; i < sl; i++) {
            mat[xx][yy] = '#';
            int d = s >> ((sl - 1 - i) << 1) & 3;
            xx += dir[d][0];
            yy += dir[d][1];
        }
        if (sl == 2) mat[xx][yy] = '#';

        for (int d = 0; d < 4; d++) {
            xx = x + dir[d][0];
            yy = y + dir[d][1];
            int ns = s >> 2 | (d ^ 2) << ((sl - 2) << 1);
            if (xx >= 0 && xx < n && yy >= 0 && yy < m && mat[xx][yy] != '#' && f[xx][yy][ns] == INF) {
                if (mat[xx][yy] == '@') {
                    cout << f[x][y][s] + 1 << endl;
                    return 0;
                }
                f[xx][yy][ns] = f[x][y][s] + 1;
                Q.push((xx << 20) + (yy << 16) + ns);
            }
        }

        xx = x, yy = y;
        for (int i = 1; i < sl; i++) {
            mat[xx][yy] = '.';
            int d = s >> ((sl - 1 - i) << 1) & 3;
            xx += dir[d][0];
            yy += dir[d][1];
        }
        if (sl == 2) mat[xx][yy] = '.';
    }

    cout << -1 << endl;

    return 0;
}

