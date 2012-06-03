#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, cnt;
bool vis[100][100];
string paper[100];

void floodfill(int i, int j)
{
    if (vis[i][j]) return ;
    vis[i][j] = true;
    cnt++;

    if (i > 0 && paper[i - 1][j] == '#') floodfill(i - 1, j);
    if (i + 1 < n && paper[i + 1][j] == '#') floodfill(i + 1, j);
    if (j > 0 && paper[i][j - 1] == '#') floodfill(i, j - 1);
    if (j + 1 < m && paper[i][j + 1] == '#') floodfill(i, j + 1);
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> paper[i];

    int ans = INF;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (paper[i][j] == '.') continue;
            tot++;

            cnt = 0;
            if (i > 0 && paper[i - 1][j] == '#') cnt++;
            if (i + 1 < n && paper[i + 1][j] == '#') cnt++;
            if (j > 0 && paper[i][j - 1] == '#') cnt++;
            if (j + 1 < m && paper[i][j + 1] == '#') cnt++;
            if (cnt) ans = min(ans, cnt);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (paper[i][j] == '.') continue;
            paper[i][j] = '.';
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < m; l++) {
                    if (paper[k][l] == '#') {
                        memset(vis, 0, sizeof(vis));
                        cnt = 0;
                        floodfill(k, l);
                        goto NEXT_STEP;
                    }
                }
            }
NEXT_STEP:
            if (cnt != tot - 1) {
                ans = 1;
                goto FINAL_STEP;
            }

            paper[i][j] = '#';
        }
    }

FINAL_STEP:
    if (ans == INF || tot - ans <= 1) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}

