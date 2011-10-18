int josephus(int n, int m)
{

/*
 * orignal:         1,         2, ... , m - 1, m, m + 1, m + 2, ... , i
 * relabel: i - m + 1, i - m + 2, ... , i - 1, 0,     1,     2, ... , i - m
 * if No.x is killed in next round,
 * its actually label before relabeling is (x + m - 1) % i + 1
 *
 * Hence, we get:
 * f[1] = 1 (the last person must be relabeled 1)
 * f[i] = (f[i - 1] + m - 1) % i + 1, for i in 2, 3, ... , n
 */

    int x = 1;
    for (int i = 2; i <= n; i++) x = (x + m - 1) % i + 1;
    return x;
}
