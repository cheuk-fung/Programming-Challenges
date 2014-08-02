/*
 *  SRC: POJ 1159
 * PROB: Palindrome
 * ALGO: DP
 * DATE: Jul 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

inline int min(int a, int b)
{
    return a < b ? a : b;
}

int f[3][5010];

int main()
{
    int n;
    scanf("%d", &n);

    char s[n + 10];
    scanf("%s", s);

    for (int i = 0; i + 1 < n; i++)
        f[1][i] = s[i] == s[i + 1] ? 0 : 1;
    for (int l = 2; l < n; l++)
        for (int i = 0; i + l < n; i++) {
            f[l % 3][i] = min(f[(l - 1) % 3][i], f[(l - 1) % 3][i + 1]) + 1;
            f[l % 3][i] = min(f[l % 3][i], f[(l - 2) % 3][i + 1] + (s[i] == s[i + l] ? 0 : 2));
            }

    printf("%d\n", f[(n - 1) % 3][0]);

    return 0;
}
