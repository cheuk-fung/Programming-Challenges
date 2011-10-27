/*
ID: os.idea1
LANG: C
TASK: lamps
*/
#include <stdio.h>
#include <string.h>

long n, c;
int p, q, sum, on[101], off[101];
char LAMPS[101][101];

void decimal_to_binary(int p, char a[])
{
    int q = 0;
    while (p)
    {
        a[q++] = p % 2 + '0';
        p /= 2;
    }
    a[q] = '\0';
}

int check(int p, char button[])
{
    char tmp[5];
    decimal_to_binary(p, tmp);
    int i, q = 0;
    for (i = 0; i < strlen(tmp); i++)
        if (tmp[i] - '0') q++;
    if (q > c) return 0;
    if (((4 - q) % 2) == (c % 2))
    {
        sprintf(button, "%s", tmp);
        return 1;
    }
    return 0;
}

void MakeChange(char button[])
{
    int j;
    char lamp[n + 1];
    memset(lamp, '1', sizeof(lamp));
    if (button[3] == '1')
        for (j = 0; j < n; j++) lamp[j] = (lamp[j] - '0') ^ 1 + '0';
    if (button[2] == '1')
        for (j = 0; j < n; j += 2) lamp[j] = (lamp[j] - '0') ^ 1 + '0';
    if (button[1] == '1')
        for (j = 1; j < n; j += 2) lamp[j] = (lamp[j] - '0') ^ 1 + '0';
    if (button[0] == '1')
        for (j = 0; j < n; j += 3) lamp[j] = (lamp[j] - '0') ^ 1 + '0';
    for (j = 0; j < p; j++)
        if (lamp[on[j] - 1] == '0') return;
    for (j = 0; j < q; j++)
        if (lamp[off[j] - 1] == '1') return;
    lamp[n] = '\0';
    sprintf(LAMPS[sum++], "%s", lamp);
}

void swap(char a[], char b[])
{
    char c[101];
    sprintf(c, "%s", a);
    sprintf(a, "%s", b);
    sprintf(b, "%s", c);
}

void sort(int l, int r)
{
    int i = l, j = r;
    char mid[101];
    sprintf(mid, "%s", LAMPS[(l + r) / 2]);
    while (i < j)
    {
        while (strcmp(LAMPS[i], mid) < 0) i++;
        while (strcmp(LAMPS[j], mid) > 0) j--;
        if (i <= j) swap(LAMPS[i++], LAMPS[j--]);
    }
    if (i < r) sort(i, r);
    if (j > l) sort(l, j);
}

int main()
{
    FILE *fin=fopen("lamps.in","r");
    FILE *fout=fopen("lamps.out","w");

    fscanf(fin, "%ld %ld", &n, &c);
    long tmp;
    while (1)
    {
        fscanf(fin, "%d", &tmp);
        if (tmp == -1) break;
        on[p++] = tmp;
    }
    while (1)
    {
        fscanf(fin, "%d", &tmp);
        if (tmp == -1) break;
        off[q++] = tmp;
    }

    if (c == 0)
    {
        if (q)
        {
            fprintf(fout, "IMPOSSIBLE\n");
            fclose(fin); fclose(fout);
            return 0;
        }
        else
        {
            int i;
            for (i = 0; i < n; i++) fprintf(fout, "1");
            fprintf(fout, "\n");
            fclose(fin); fclose(fout);
            return 0;
        }
    }

    int i;
    char button[5];
    for (i = 0; i < 16; i++)
        if (check(i, button))
            MakeChange(button);

    sort(0, sum - 1);
    for (i = 0; i < sum; i++) fprintf(fout, "%s\n", LAMPS[i]);
    if (sum == 0) fprintf(fout, "IMPOSSIBLE\n");

    fclose(fin); fclose(fout);

    return 0;
}
