/*
ID: os.idea1
LANG: C
TASK: contact
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;

int a, b, n, ls, tot, f[21][10001], bin[21];
char s[200001];

struct ANS
{
    int sum, len, num;
}ans[130001];

void BinToDec(int p, int q)
{
    int i, sum = 0;
    for (i = p; i < p + q; i++)
	sum += bin[p + q - i - 1] * (s[i] - '0');
    if (!f[q][sum])
    {
	ans[tot].sum = sum;
	ans[tot].len = q;
	ans[tot].num++;
	f[q][sum] = 1 + tot++;
    }
    else
	ans[f[q][sum] - 1].num++;
}

void qsort(int l, int r)
{
    int i = l, j = r;
    struct ANS mid = ans[(l + r) / 2], tmp;
    while (i < j)
    {
	while (ans[i].num > mid.num ||
	       (ans[i].num == mid.num && ans[i].len < mid.len) ||
	       (ans[i].num == mid.num && ans[i].len == mid.len && ans[i].sum < mid.sum)) i++;
	while (ans[j].num < mid.num ||
	       (ans[j].num == mid.num && ans[j].len > mid.len) ||
	       (ans[j].num == mid.num && ans[j].len == mid.len && ans[j].sum > mid.sum)) j--;
	if (i <= j)
	{
	    tmp = ans[i];
	    ans[i] = ans[j];
	    ans[j] = tmp;
	    i++; j--;
	}
    }
    if (i < r) qsort(i, r);
    if (l < j) qsort(l, j);
}

void DecToBin(int p, int q)
{
    int c[20];
    int len = 0, i;
    while (p)
    {
	c[len++] = p % 2;
	p >>= 1;
    }
    for (i = 0; i < q - len; i++) fprintf(fout, "0");
    for (i = len - 1; i >= 0; i--) fprintf(fout, "%d", c[i]);
}

int main()
{
    fin = fopen("contact.in", "r");
    fout = fopen("contact.out", "w");

    fscanf(fin, "%d %d %d\n", &a, &b, &n);
    while (!feof(fin))
    {
	char c;
	fscanf(fin, "%c", &c);
	if (c != '\n') s[ls++] = c;
    }
    int i, j;
    bin[0] = 1;
    for (i = 1; i <= 20; i++) bin[i] = bin[i - 1] << 1;
    for (i = a; i <= b; i++)
	for (j = 0; j <= ls - i; j++)
	    BinToDec(j, i);

    qsort(0, tot - 1);

    int now = ans[0].num, k = 1, t = 0;
    fprintf(fout, "%d\n", ans[0].num);
    DecToBin(ans[0].sum, ans[0].len); 
    for (i = 1; i < tot; i++)
    {
	if (ans[i].num == now)
	{
	    if (++t % 6 == 1) fprintf(fout, "\n");
	    else fprintf(fout, " ");
	    DecToBin(ans[i].sum, ans[i].len); 
	}
	else
	{
	    if (k++ >= n) break;
	    now = ans[i].num;
	    t = 1;
	    fprintf(fout, "\n%d\n", ans[i].num);
	    DecToBin(ans[i].sum, ans[i].len); 
	}
    }
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);
    return 0;
}

