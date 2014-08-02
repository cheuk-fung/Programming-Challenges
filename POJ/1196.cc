/*
 *  SRC: POJ 1196
 * PROB: Twofive
 * ALGO: Memorize Search
 * DATE: Oct 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int f[6][6][6][6][6];

int n;
char str[30];
int y[5], vis[256];

struct Position {
    int x, y;
} pos[256];

int solve()
{
    for (int i = 0; i < 5; i++) if (y[i] > 5) return 0;
    for (int i = 1; i < 5; i++) if (y[i] > y[i - 1]) return 0;

    if (f[y[0]][y[1]][y[2]][y[3]][y[4]] > -1)
        return f[y[0]][y[1]][y[2]][y[3]][y[4]];

    int curr = 'A';
    for (int i = 0; i < 5; i++) curr += y[i];
    if (pos[curr].y > -1) {
        if (pos[curr].x != y[pos[curr].y])
            return f[y[0]][y[1]][y[2]][y[3]][y[4]] = 0;
        y[pos[curr].y]++;
        int res = solve();
        y[pos[curr].y]--;
        return f[y[0]][y[1]][y[2]][y[3]][y[4]] = res;
    }

    int res = 0;
    for (int i = 0; i < 5; i++) {
        y[i]++;
        res += solve();
        y[i]--;
    }

    return f[y[0]][y[1]][y[2]][y[3]][y[4]] = res;
}

void solve_n()
{
    memset(pos, 0xff, sizeof(pos));

    for (int i = 0; i < 25; i++)
        for (int j = 'A'; j < 'Z'; j++) {
            if (vis[j]) continue;

            pos[j].x = i / 5;
            pos[j].y = i % 5;

            memset(f, 0xff, sizeof(f));
            f[5][5][5][5][5] = 1;

            int tmp = solve();
            if (tmp >= n) {
                vis[j] = 1;
                putchar(j);
                break;
            }
            else n -= tmp;

            pos[j].x = pos[j].y = -1;
        }

    putchar(10);
}

void solve_w()
{
    memset(pos, 0xff, sizeof(pos));

    int ans = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = 'A'; j < str[i]; j++) {
            if (vis[j]) continue;

            pos[j].x = i / 5;
            pos[j].y = i % 5;

            memset(f, 0xff, sizeof(f));
            f[5][5][5][5][5] = 1;

            ans += solve();

            pos[j].x = pos[j].y = -1;
        }
        vis[str[i]] = 1;
        pos[str[i]].x = i / 5;
        pos[str[i]].y = i % 5;
    }

    printf("%d\n", ans + 1);
}

int main()
{
    char c = getchar();
    if (c == 'N') {
        scanf("%d", &n);
        solve_n();
    }
    else {
        scanf("%s", str);
        solve_w();
    }

    return 0;
}
