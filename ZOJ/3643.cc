/*
 *  SRC: ZOJ 3643
 * PROB: Keep Deleting
 * ALGO: KMP
 * DATE: Aug 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

char A[300], B[520000];
int prn[300], que[520000];

void kmp_init(int *prn, char *b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != b[i]) j = prn[j - 1];
        if (b[j] == b[i]) j++;
        prn[i] = j;
    }
}

int kmp(int *prn, char *a, char *b, int n, int m)
{
    int cnt = 0, head = 0, tail = 0;
    que[tail++] = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && b[j] != a[i]) j = prn[j - 1];
        if (b[j] == a[i]) j++;
        if (j == m) {
            cnt++;
            j = que[head];
            tail = head + 1;
            head -= m - 1;
            if (head < 0) head = 0;
        } else {
            que[tail++] = j;
            if (tail - head > m) head++;
        }
    }
    return cnt;
}

int main()
{
    while (~scanf(" %s %s", A, B)) {
        int m = strlen(A), n = strlen(B);
        kmp_init(prn, A, m);

        int r = kmp(prn, B, A, n, m);
        printf("%d\n", r);
    }

    return 0;
}

