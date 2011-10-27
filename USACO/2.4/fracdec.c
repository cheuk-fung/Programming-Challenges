/*
ID: os.idea1
LANG: C
TASK: fracdec
*/
#include <stdio.h>
#include <string.h>

long n, d;
int cbool[100000], num[100000];

int main()
{
    FILE *fin = fopen("fracdec.in","r");
    FILE *fout = fopen("fracdec.out","w");

    fscanf(fin, "%ld %ld", &n, &d);

    if (n % d == 0)
    {
        fprintf(fout, "%ld.0\n", n / d);
        fclose(fin); fclose(fout);
        return 0;
    }

    fprintf(fout, "%ld.", n / d);
    char ss[100000];
    sprintf(ss, "%ld.", n / d);
    long len = strlen(ss), s, i, j;

    for (;;)
    {
        s = n % d;
        if (s == 0 || cbool[s]) break;
        n = s * 10;
        num[++i] = n / d;
        cbool[s] = i;
    }
    if (s == 0)
        for (j = 1; j <= i; j++)
        {
            fprintf(fout, "%ld", num[j]);
            if (!((j + len) % 76) && j != i) fprintf(fout, "\n");
        }
    else
    {
        for (j = 1; j < cbool[s]; j++)
        {
            fprintf(fout, "%ld", num[j]);
            if (!((j + len) % 76)) fprintf(fout, "\n");
        }
        fprintf(fout, "(");
        for (j = cbool[s]; j <= i; j++)
        {
            fprintf(fout, "%ld", num[j]);
            if (!((j + len + 1) % 76)) fprintf(fout, "\n");
        }
        fprintf(fout, ")");
    }
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);
    return 0;
}
