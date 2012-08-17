#include <cstdio>

int A[9], B[3][3];

bool check(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!A[i * n + j]) return true;
            if (i + 1 < n && !A[(i + 1) * n + j]) return true;
            if (j + 1 < n && !A[i * n + j + 1]) return true;

            int bigger = 0;
            if (i > 0) bigger += A[(i - 1) * n + j] > A[i * n + j];
            if (i + 1 < n) bigger += A[(i + 1) * n + j] > A[i * n + j];
            if (j > 0) bigger += A[i * n + j - 1] > A[i * n + j];
            if (j + 1 < n) bigger += A[i * n + j + 1] > A[i * n + j];
            if (bigger != B[i][j]) return false;
        }
    }
    return true;
}

bool generate(int n, int cnt)
{
    if (!check(n)) return false;
    if (cnt == n * n) return true;

    for (int i = 1; i <= 9; i++) {
        A[cnt] = i;
        if (generate(n, cnt + 1)) return true;
        A[cnt] = 0;
    }
    return false;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    if (generate(n, 0)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d%c", A[i * n + j], j + 1 == n ? '\n' : ' ');
            }
        }
    } else {
        puts("NO SOLUTION");
    }

    return 0;
}
