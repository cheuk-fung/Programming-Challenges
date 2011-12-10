/*
 *  SRC: NKOJ 2186
 * PROB: Exercise 6 动态规划
 * ALGO: DP
 * DATE: Dec 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

int f[2][2010];
char A[2010], B[2010];
int K;

inline int min(int x, int y) { return x < y ? x : y; }

void next(char *s)
{
    while ((*s = getchar()) != '\n') s++;
    *s = '\0';
}

int next_int()
{
    char c;
    while (!isdigit(c = getchar())) ;
    int res = c - '0';
    while (isdigit(c = getchar()))
        res = res * 10 + c - '0';
    return res;
}

int main()
{
    next(A);
    next(B);
    K = next_int();

    int a_len = strlen(A),
        b_len = strlen(B);

    for (int j = 1; j <= b_len; j++) f[0][j] = f[0][j - 1] + K;

    for (int i = 1, p = 0, q = 1; i <= a_len; i++) {
        f[q][0] = i * K;
        for (int j = 1; j <= b_len; j++)
            f[q][j] = min(f[p][j - 1] + abs(A[i - 1] - B[j - 1]), \
                          min(f[p][j], f[q][j - 1]) + K);
        p ^= 1;
        q ^= 1;
    }

    printf("%d\n", f[a_len & 1][b_len]);

    return 0;
}
