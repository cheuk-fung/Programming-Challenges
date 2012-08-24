#include <cstdio>
#include <cstring>

const short int INF = 0x3f3f;

int m, n;
short int f[71][1 << 7][1 << 7];
int initstate[71];

inline int MIN(int x, int y) { return x < y ? x : y; }
inline int chkbit(int x, int y) { return (x >> y) & 1; }
inline int setbit(int x, int y) { return x | (1 << y); }
inline int setbit(int x, int y, int z) { return x | (1 << y) | (1 << z); }

void dfs(int s, int ns, int ps, int v, int x, int y)
{
    if (y == n) {
        f[x + 1][ns][s] = MIN(f[x + 1][ns][s], v);
        return ;
    }

    if (chkbit(s, y) == 1) return dfs(s, ns, ps, v, x, y + 1);

    if (chkbit(ps, y) == 1 && (y == 0 || (y > 0 && chkbit(s, y - 1) == 1))) dfs(s, ns, ps, v, x, y + 1);
    if (y + 1 < n && chkbit(s, y + 1) == 0) dfs(setbit(s, y, y + 1), ns, ps, v + 1, x, y + 2);
    if (chkbit(ns, y) == 0) dfs(setbit(s, y), setbit(ns, y), ps, v + 1, x, y + 1);
}

int main(int argc, char *argv[])
{
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        char s[10];
        scanf("%s", s);
        for (int j = 0; j < n; j++) {
            if (s[j] == '*') initstate[i] |= 1 << j;
        }
    }

    memset(f, 0x3f, sizeof f);
    dfs(initstate[0], initstate[1], (1 << n) - 1, 0, 0, 0);
    for (int i = 1; i < m; i++) {
        for (int ps = 0; ps < 1 << n; ps++) {
            for (int s = 0; s < 1 << n; s++) {
                if (f[i][s][ps] == INF) continue;
                dfs(s, initstate[i + 1], ps, f[i][s][ps], i, 0);
            }
        }
    }

    int ans = INF;
    for (int ps = 0; ps < 1 << n; ps++) {
        ans = MIN(ans, f[m][0][ps]);
    }
    printf("%d\n", ans);

    return 0;
}
