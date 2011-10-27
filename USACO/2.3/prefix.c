/*
ID: os.idea1
LANG: C
TASK: prefix
*/
#include <stdio.h>
#include <string.h>

char set[201][11], s[2000001];
int f[2000001], g[1000000];

int main()
{
    FILE *fin=fopen("prefix.in","r");
    FILE *fout=fopen("prefix.out","w");

    long p = 0, q, i, j, k;
    char c;
    fscanf(fin, "%c", &c);
    while (c != '.')
    {
        q = 0;
        while (c != ' ' && c != '\n')
        {
            set[p][q++] = c;
            fscanf(fin, "%c", &c);
        }
        set[p++][q] = '\0';
        fscanf(fin, "%c", &c);
    }
    long long tmp;
    for (i = 0; i < p; i++)
    {
        tmp = 0;
        for (j = 0; j < strlen(set[i]); j++)
        {
            tmp *= 10;
            tmp += set[i][j] - 'A' + 1;
        }
        tmp %= 999997;
        //printf("%d\n", tmp);
        g[tmp] = 1;
    }
    //for (i = 0; i < p; i++) printf("%s\n", set[i]);
    q = 1;
    while (fscanf(fin, "%c", &c) == 1)
        if (c != '\n') s[q++] = c;
    s[0] = '0'; s[q] = '\0';
    //printf("%s\n", s);
    long len = strlen(s);
    f[0] = 1;
    for (i = 1; i < len; i++)
        for (j = 1; j <= 10; j++)
        {
            char t[11];
            k = 0;
            if (i >= j)
                for ( ; k < j; k++) t[k] = s[i - j + k + 1];
            t[k] = '\0';
            if (!k) continue;
            //printf("%s\n", t);
            tmp = 0;
            for (k = 0; k < j; k++)
            {
                tmp *= 10;
                tmp += t[k] - 'A' + 1;
            }
            tmp %= 999997;
            //printf("%d\n", tmp);
            if (g[tmp] && f[i - j])
            {
                f[i] = 1;
                break;
            }
        }
    //for (i = 1; i < len; i++) printf("%d", f[i]); printf("\n");
    for (i = len - 1; i > 0; i--)
        if (f[i]) break;
    fprintf(fout, "%ld\n", i);

    fclose(fin); fclose(fout);

    return 0;
}
