/*
 *  SRC: POJ 1274
 * PROB: The Perfect Stall
 * ALGO: Hungarian
 * DATE: Sep 27, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, m, ans, cost[201][201], match[201], used[201];

int find_path(int p)
{
    for (int i = 1; i <= m; i++)
        if (cost[p][i] && !used[i])
        {
            used[i] = 1;
            int t = match[i];
            match[i] = p;
            if (t == -1 || find_path(t)) return 1;
            match[i] = t;
        }
    return 0;
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(cost, 0, sizeof(cost));
        ans = 0;

        for (int i = 1; i <= n; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++)
            {
                int l;
                scanf("%d", &l);
                cost[i][l] = 1;
            }
        }

        memset(match, 0xff, sizeof(match));

        for (int i = 1; i <= n; i++)
        {
            memset(used, 0, sizeof(used));
            if (find_path(i)) ans++;
        }

        printf("%d\n", ans);
    }

    return 0;
}
