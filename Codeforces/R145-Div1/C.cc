#include <cstdio>
#include <cmath>

FILE *fin, *fout;

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    int n;
    fscanf(fin, "%d", &n);
    int m = ceil(log2(n));
    fprintf(fout, "%d\n", m);
    for (int i = 1, p = 1; i <= m; i++) {
        p <<= 1;
        int cnt = 0;
        for (int j = 1; j <= n; j += p) {
            for (int k = 0; k < p >> 1 && j + k <= n; k++) {
                cnt++;
            }
        }
        fprintf(fout, "%d", cnt);
        for (int j = 1; j <= n; j += p) {
            for (int k = 0; k < p >> 1 && j + k <= n; k++) {
                fprintf(fout, " %d", j + k);
            }
        }
        fputc(10, fout);
    }

    return 0;
}

