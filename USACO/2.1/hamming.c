/*
ID: os.idea1
LANG: C
TASK: hamming
*/
#include <stdio.h>

int n, b, d;
int i = 0, ham[1000] = {0};

int hamming(int p)
{
    int k, tmp;
    for (k = 0; k <= i; k++)
    {
        int sum = 0;
        tmp = p ^ ham[k];
        while (tmp)
        {
            sum += tmp & 1;
            tmp >>= 1;
        }
        if (sum < d) return 0;
    }
    return 1;
}

int main()
{
    FILE *fin=fopen("hamming.in","r");
    FILE *fout=fopen("hamming.out","w");

    fscanf(fin, "%d %d %d", &n, &b, &d);

    int j;
    for (j = 1; j <= 2 << b; j++)
        if (hamming(j)) ham[++i] = j;

    for (i = 1; i < n; i++)
    {
        fprintf(fout, "%d", ham[i - 1]);
        if (i % 10 == 0) fprintf(fout, "\n");
        else fprintf(fout, " ");
    }
    fprintf(fout, "%d\n", ham[n - 1]);

    fclose(fin); fclose(fout);

    return 0;
}
