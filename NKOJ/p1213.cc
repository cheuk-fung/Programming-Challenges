/*
 *  SRC: NKOJ p1213
 * PROB: Power Strings
 * ALGO: KMP
 * DATE: Jul 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

char s[1000010];
int next[1000010];

inline void KMPInit(int* P, char* B, int m)
{
    P[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && B[j] != B[i]) j = P[j - 1];
        if (B[j] == B[i]) j++;
        P[i] = j;
    }
}

int main()
{
    while (scanf("%s", s) != EOF) {
        if (s[0] == '.') break;
        int len = strlen(s);
        KMPInit(next, s, len);
        if (len % (len - next[len - 1]) == 0)
            printf("%d\n", len / (len - next[len - 1]));
        else puts("1");
    }

    return 0;
}
