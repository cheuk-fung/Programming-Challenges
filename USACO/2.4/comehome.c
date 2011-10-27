/*
ID: os.idea1
LANG: C
TASK: comehome
*/
#include <stdio.h>

long p, f[200][200], ans = 10000000;

int main()
{
    FILE *fin = fopen("comehome.in","r");
    FILE *fout = fopen("comehome.out","w");

    fscanf(fin, "%ld\n", &p);
    char a, b;
    long i, j, k;
    for (i = 0; i < p; i++)
    {
        fscanf(fin, "%c %c %ld\n", &a, &b, &j);
        if (f[(int)a][(int)b] && j > f[(int)a][(int)b]) continue;
        f[(int)a][(int)b] = j;
        f[(int)b][(int)a] = j;
    }

    for (k = (int)'A'; k <= (int)'z'; k++)
        for (i = (int)'A'; i <= (int)'z'; i++)
        {
            if (i == k) continue;
            for (j = (int)'A'; j <= (int)'z'; j++)
            {
                if (j == i || j == k) continue;
                if (f[i][k] > 0 && f[k][j] > 0 && (f[i][k] + f[k][j] < f[i][j] || f[i][j] == 0))
                    f[i][j] = f[i][k] + f[k][j];
            }
        }

    for (i = (int)'A'; i < (int)'Z'; i++)
        if(0 < f[i][(int)'Z'] && f[i][(int)'Z'] < ans)
        {
            j = i;
            ans = f[i][(int)'Z'];
        }

    fprintf(fout, "%c %ld\n", (char)j, ans);

    fclose(fin); fclose(fout);
    return 0;
}
