inline void KMPInit(int* P, char* B, int m)
{
    P[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && B[j] != B[i]) j = P[j - 1];
        if (B[j] == B[i]) j++;
        P[i] = j;
    }
}

inline int KMP(int* P, char* A, char* B, int n, int m)
{
    int res = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && B[j] != A[i]) j = P[j - 1];
        if (B[j] == A[i]) j++;
        if (j == m) {
            res++;
            j = P[j - 1];
        }
    }

    return res;
}
