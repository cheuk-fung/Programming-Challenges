/*
 *  SRC: HDOJ ACM Steps
 * PROB: A+B for Input-Output Practice (IV)
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            ans += t;
        }
        printf("%d\n", ans);
    }

    return 0;
}
