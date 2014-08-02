/*
 *  SRC: HDOJ 3401
 * PROB: Trade
 * ALGO: Monotone Priority Queue + DP
 * DATE: Aug 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int NEGINF = 0xc0c0c0c0;

int aque[2012], bque[2012];
int f[2012][2012], g[2012];

inline int MAX(int x, int y) { return x > y ? x : y; }
inline int key(int a, int x) { return g[x] + x * a; }

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, MaxP, W;
        scanf("%d%d%d", &n, &MaxP, &W);

        int ans = NEGINF;
        memset(f, 0xc0, sizeof f);
        memset(g, 0xc0, sizeof g);
        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            int ap, bp, as, bs;
            scanf("%d%d%d%d", &ap, &bp, &as, &bs);

            int k = MAX(i - W - 1, 0);
            for (int j = 0; j <= MaxP; j++) {
                g[j] = MAX(g[j], f[k][j]);
            }

            int ahead = 0, atail = 0;
            for (int j = 0; j <= MaxP; j++) {
                while (ahead < atail && key(ap, aque[atail - 1]) <= key(ap, j)) atail--;
                while (ahead < atail && j - aque[ahead] > as) ahead++;
                aque[atail++] = j;
                f[i][j] = MAX(f[i][j], key(ap, aque[ahead]) - j * ap);
                ans = MAX(ans, f[i][j]);
            }

            int bhead = 0, btail = 0;
            for (int j = MaxP; j >= 0; j--) {
                while (bhead < btail && key(bp, bque[btail - 1]) <= key(bp, j)) btail--;
                while (bhead < btail && bque[bhead] - j > bs) bhead++;
                bque[btail++] = j;
                f[i][j] = MAX(f[i][j], key(bp, bque[bhead]) - j * bp);
                ans = MAX(ans, f[i][j]);
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

