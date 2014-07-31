/*
ID: os.idea1
LANG: C
TASK: runround
*/
#include <stdio.h>
#include <string.h>

int runround(long m)
{
    int p = 0, i = m, tmp[10], num[10], used[10];
    memset(used, 0, sizeof(used));
    used[0] = 1;
    while (i)
    {
        tmp[p] = i % 10;
        if (used[tmp[p]]) return 0;
        used[tmp[p++]] = 1;
        i /= 10;
    }
    memset(used, 0, sizeof(used));
    for (i = 0; i < p; i++) num[i] = tmp[p - i - 1];
    int q = p;
    i = 0;
    while (q)
    {
        used[num[i]] = 1;
        i = (num[i] + i) % p;
        q--;
    }
    if (i) return 0;
    for (i = 0; i < p; i++)
        if (!used[num[i]]) return 0;
    return 1;
}

int main()
{
    FILE *fin=fopen("runround.in","r");
    FILE *fout=fopen("runround.out","w");

    long m;
    fscanf(fin, "%ld", &m);
    while (1 + 1 == 2)
    {
        m++;
        if (runround(m)) break;
    }

    fprintf(fout, "%ld\n", m);

    fclose(fin); fclose(fout);

    return 0;
}
