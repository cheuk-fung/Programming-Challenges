/*
 *  SRC: NKOJ 1890
 * PROB: Moving ACMers
 * ALGO: Greedy
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, m, ans = 1, vis[1000];

int main()
{
    scanf("%d%d", &n, &m);

    int cnt = 0, num;
    while (scanf("%d", &num) != EOF) {
        if (vis[num] == ans) continue;
        
        cnt++;
        if (cnt == n) {
            ans++;
            cnt = 1;
        }
        vis[num] = ans;
    }

    printf("%d\n", ans - 1);

    return 0;
}
