/*
ID: os.idea1
LANG: C
TASK: zerosum
*/
#include <stdio.h>

FILE *fin, *fout;
int n;

void process(int p, int sum, int last, char s[])
{
    if (p > n)
    {
        if (sum) return;
        int i;
        fprintf(fout, "1");
        for (i = 2; i <= n; i++) fprintf(fout, "%c%d", s[i], i);
        fprintf(fout, "\n");
        return;
    }

    int ts = sum, tmp = 0, i;
    for (i = last; i < p; i++) tmp = tmp * 10 + i;
    if (s[last] == '+' || last == 0) ts = sum - tmp + tmp * 10 + p;
    else ts = sum + tmp - tmp * 10 - p;
    s[p] = ' ';
    process(p + 1, ts, last, s);

    if (p == 1) return;

    ts = sum + p;
    s[p] = '+';
    process(p + 1, ts, p, s);

    ts = sum - p;
    s[p] = '-';
    process(p + 1, ts, p, s);
}

int main()
{
    fin=fopen("zerosum.in","r");
    fout=fopen("zerosum.out","w");

    fscanf(fin, "%d", &n);

    char symbol[10];
    process(1, 0, 0, symbol);

    fclose(fin); fclose(fout);

    return 0;
}
