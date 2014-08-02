/*
 *  SRC: HDOJ 4451
 * PROB: Dressing
 * ALGO: NULL
 * DATE: Oct 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

int pl[1010];

struct Edge {
    int type;
    int v;
} e[2000010];

char s[100];

int main()
{
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        memset(pl, 0, sizeof pl);

        int p;
        scanf("%d", &p);
        for (int i = 0; i < p; i++) {
            int u, v;
            scanf("%s%d%*s%d", s, &u, &v);
            if (s[0] == 'c') {
                e[i].type = 0;
                pl[v]++;
                e[i].v = v;
            } else {
                e[i].type = 1;
                e[i].v = u;
            }
        }
        int ans = n * m * k;
        for (int i = 0; i < p; i++) {
            if (e[i].type == 0) {
                ans -= k;
            } else {
                ans -= n - pl[e[i].v];
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

