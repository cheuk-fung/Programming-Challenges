/*
ID: os.idea1
LANG: C
TASK: frac1
*/
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

struct number
{
    char s[100];
    float f;
}a[10000];

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

void swap(struct number *a, struct number *b)
{
    struct number tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int l, int r)
{
    int i = l, j = r;
    float mid = a[(l + r) / 2].f;
    while (i < j)
    {
        while (a[i].f < mid) i++;
        while (a[j].f > mid) j--;
        if (i <= j) swap(&a[i++], &a[j--]);
    }

    if (i < r) sort(i, r);
    if (j > l) sort(l, j);
}

int main()
{
    FILE *fin=fopen("frac1.in","r");
    FILE *fout=fopen("frac1.out","w");

    int n;
    fscanf(fin, "%d", &n);

    int i, j, sum = 0;
    a[0].f = 0;
    strcpy(a[0].s, "0/1");
    for (i = 2; i <= n; i++)
        for (j = 0; j < i; j++)
            if (gcd(j, i) == 1)
            {
                a[++sum].f = (float)j / (float)i;
                //char tmp1[10], tmp2[10];
                //itoa(j, tmp1, 10);
                //itoa(i, tmp2, 10);
                sprintf(a[sum].s, "%d/%d", j, i);
                //strcat(tmp1, "/");
                //strcat(tmp1, tmp2);
                //strcpy(a[sum].s, tmp1);
                //printf("%s\n", a[sum].s);
            }

    sort(1, sum);

    for (i = 0; i <= sum; i++) fprintf(fout, "%s\n", a[i].s);
    fprintf(fout, "1/1\n");

    fclose(fin); fclose(fout);

    return 0;
}
