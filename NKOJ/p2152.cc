/*
 *  SRC: NKOJ
 * TASK: 道路遊戲
 * ALGO: DP [The DP function I worte was WRONG!]
 * DATE: 03/22/2011 
 *
 * Created by Leewings Ac
 */

#include	<cstdio>
#include	<climits>

inline int pre(int a, int n)
{
    return (a - 1 + n) % n;
}

int main()
{
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    int v[n][m], cost[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &v[i][j]);
    for (int i = 0; i < n; i++) scanf("%d", &cost[i]);

    int f[n], step[n], ans = INT_MIN, last = 0;
    for (int i = 0; i < n; i++)
        f[i] = step[i] = 0;
    for (int i = 0; i < m; i++) {
        int t_f = f[pre(0, n)], t_step = step[pre(0, n)];
        for (int j = 0; j < n; j++) {
            int a = INT_MIN;
            if (i && t_step < p) a = t_f + v[pre(j, n)][i];
            int b = last + v[pre(j, n)][i] - cost[pre(j, n)];
            t_f = f[j];
            if (a > b) {
                f[j] = a;
                int tt_step = step[j];
                step[j] = t_step + 1;
                t_step = tt_step;
            }
            else {
                f[j] = b;
                t_step = step[j];
                step[j] = 1;
            }
            if (f[j] > ans) ans = f[j];
        }
        last = ans;
    }

    printf("%d\n", last);

    return 0;
}				/* ----------  end of function main  ---------- */
