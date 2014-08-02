/*
 *  SRC: HDOJ ACM Steps
 * PROB: A+B for Input-Output Practice (V)
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            ans += t;
        }
        printf("%d\n", ans);
        if (jobs) printf("\n");
    }

    return 0;
}
