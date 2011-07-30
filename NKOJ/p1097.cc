/*
 *  SRC: NKOJ p1097
 * PROB: Prerequisites?
 * ALGO: hash
 * DATE: Jul 28, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int f[10000];

int main()
{
    int k, m;
    for (int task = 1; scanf("%d%d", &k, &m) == 2; task++) {
        for (int i = 0; i < k; i++) {
            int t;
            scanf("%d", &t);
            f[t] = task;
        }
        bool graduate = true;
        for (int i = 0; i < m; i++) {
            int c, r, cnt = 0;
            scanf("%d%d", &c, &r);
            for (int j = 0; j < c; j++) {
                int t;
                scanf("%d", &t);
                if (f[t] == task) cnt++;
            }
            if (cnt < r) graduate = false;
        }
        puts(graduate ? "yes" : "no");
    }

    return 0;
}

