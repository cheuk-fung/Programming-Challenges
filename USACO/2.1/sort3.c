/*
ID: os.idea1
LANG: C
TASK: sort3
*/
#include <stdio.h>

int n, t[2000], sum[4], a[4], b[4], c[4];

int main()
{
    FILE *fin=fopen("sort3.in","r");
    FILE *fout=fopen("sort3.out","w");

    int i;
    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fin, "%d", &t[i]);
        sum[t[i]]++;
    }
    for (i = 0; i < sum[1]; i++) a[t[i]]++;
    for (i = sum[1]; i < sum[1] + sum[2]; i++) b[t[i]]++;
    for (i = sum[1] + sum[2]; i < sum[1] + sum[2] + sum[3]; i++) c[t[i]]++;

    fprintf(fout, "%d\n", b[1] + c[1] + b[3] + (0 > a[3] - c[1] ? 0 : a[3] - c[1]));

    fclose(fin); fclose(fout);

    return 0;
}
