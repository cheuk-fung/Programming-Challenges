int prime(int n, int* p)
{
    bool b[n];
    int sum = 0;
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) b[i] = true;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] <= n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return sum;
}
