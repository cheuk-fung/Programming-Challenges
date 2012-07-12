/*
 *  SRC: POJ 1961
 * PROB: Period
 * ALGO: KMP
 * DATE: Jul 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

void kmp_init(int *prn, char *b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != b[i]) j = prn[j - 1];
        if (b[j] == b[i]) j++;
        prn[i] = j;
    }
}

char s[1000010];
int prn[1000010];

int main()
{
    int n, task = 1;
    while (scanf("%d", &n), n) {
        printf("Test case #%d\n", task++);

        scanf("%s", s);
        kmp_init(prn, s, n);
        for (int i = 1; i < n; i++) {
            if (s[i] == s[prn[i - 1]] && (i + 1) % (i - prn[i - 1]) == 0) {
                printf("%d %d\n", i + 1, (i + 1) / (i - prn[i - 1]));
            }
        }

        putchar(10);
    }

    return 0;
}

