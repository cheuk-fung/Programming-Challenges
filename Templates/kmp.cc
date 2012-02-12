void kmp_init(int* prn, char* b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != b[i]) j = prn[j - 1];
        if (b[j] == b[i]) j++;
        prn[i] = j;
    }
}

int kmp(int* prn, char* a, char* b, int n, int m)
{
    int cnt = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && b[j] != a[i]) j = prn[j - 1];
        if (b[j] == a[i]) j++;
        if (j == m) {
            cnt++;
            j = prn[j - 1];
        }
    }

    return cnt;
}
