/*
 *  SRC: NKOJ
 * TASK: Eat healthily
 * ALGO: CompletePack
 * DATE: 04/09/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXSUM = 1000000;

int min(int a, int b)
{
    if (a <= b) return a;
    return b;
}

void work()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int p[n], f[n], dp[m + 2000];
    for (int i = 0; i < n; i++)
        scanf("%d%d", &p[i], &f[i]);
    for (int i = 0; i <= m + 1000; i++) dp[i] = MAXSUM;
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = p[i]; j <= m + 1000; j++)
            dp[j] = min(dp[j], dp[j - p[i]] + f[i]);
    int min = MAXSUM;
    for (int i = m; i <= m + 1000; i++)
        if (dp[i] < min) min = dp[i];
    printf("%d\n", min);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) work();

    return 0;
}

