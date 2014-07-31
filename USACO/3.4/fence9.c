/*
ID: os.idea1
LANG: C
TASK: fence9
*/
#include <stdio.h>

FILE *fin, *fout;
int n, m, p;

int gcd(int a, int b)
{
    if (!a) return b;
    return gcd(b % a, a);
}

int Del(int a, int b)
{
    return ((a + 1) * (b + 1) + gcd(a, b) + 1)/ 2;
}

int main()
{
    fin = fopen("fence9.in", "r");
    fout = fopen("fence9.out", "w");

    fscanf(fin, "%d %d %d\n", &n, &m, &p);
    fprintf(fout, "%d\n", ((p > n ? p : n) + 1) * (m + 1) - Del(n, m) - Del((p > n ? p - n : n - p), m) - (p + 1) + 3);

    fclose(fin); fclose(fout);
    return 0;
}
