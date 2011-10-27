/*
ID: os.idea1
LANG: C
TASK: rect1
*/
#include <stdio.h>

struct point
{
    long x1, y1, x2, y2, c/*color*/;
}r[1001];/*rect*/

struct tree
{
    long a, b, l, r, cover, sign;
}t[20000];/*tree*/

long a, b, n, tot, color[2501], tmpcolor[1001], s1[1001], s2[1001], times = 1;

void MakeTree(long a, long b)
{
    long st = ++tot;
    t[st].a = a; t[st].b = b;
    if (a + 1 < b)
    {
        t[st].l = tot + 1;
	MakeTree(a, (a + b) / 2);
	t[st].r = tot + 1;
	MakeTree((a + b) / 2, b);
    }
}

void Insert(long p, long q, long k)
{
    if (!t[p].sign)
    {
        t[t[p].l].sign = 0;
	t[t[p].r].sign = 0;
    }

    if (!t[p].sign && r[k].y1 <= t[p].a && t[p].b <= r[k].y2)
    {
        t[p].cover = q; t[p].sign = 1;
	t[t[p].l].cover = q; t[t[p].r].cover = q;
	t[t[p].l].sign = 1; t[t[p].r].sign = 1;
        //color[r[k].c] += t[p].b - t[p].a;
	tmpcolor[k] += t[p].b - t[p].a;
    }
    else
    {
        t[p].sign = 1;
        if (r[k].y1 < (t[p].a + t[p].b) / 2 && t[p].l && q > t[t[p].l].cover) Insert(t[p].l, q, k);
	if (r[k].y2 > (t[p].a + t[p].b) / 2 && t[p].r && q > t[t[p].r].cover) Insert(t[p].r, q, k);
    }
}

int main()
{
    FILE *fin = fopen("rect1.in", "r");
    FILE *fout = fopen("rect1.out", "w");

    fscanf(fin, "%ld %ld %ld", &a, &b, &n);
    r[0].x1 = 0; r[0].y1 = 0;
    r[0].x2 = a; r[0].y2 = b;
    r[0].c = 1;
    long i, j, k = 0;
    for (i = 1; i <= n; i++)
        fscanf(fin, "%ld %ld %ld %ld %ld", &r[i].x1, &r[i].y1, &r[i].x2, &r[i].y2, &r[i].c);
    
    MakeTree(0, b);

    for (i = 0; i < a; i++)
    {
        t[1].cover = 0; t[1].sign = 0;
	long tk = 0, check = 1;
	for (j = n; j >= 0; j--)
	    if (r[j].x1 <= i && i + 1 <= r[j].x2)
	    {
		s2[tk] = j;
		if (s1[tk] != s2[tk++]) check = 0;
	    }
	if (tk != k) check = 0;
	if (check) times++;
	else
	{
	    for (j = 0; j < k; j++)
	    {
		color[r[s1[j]].c] += tmpcolor[s1[j]] * times;
		tmpcolor[s1[j]] = 0;
	    }
	    times = 1;
	    k = tk;
	    for (j = 0; j < tk; j++)
	    {
		Insert(1, i + 1, s2[j]);
		s1[j] = s2[j];
	    }
	}
    }
    for (j = 0; j < k; j++)
	color[r[s1[j]].c] += tmpcolor[s1[j]] * times;

    for (i = 1; i <= 2500; i++)
        if (color[i]) fprintf(fout, "%ld %ld\n", i, color[i]);

    fclose(fin); fclose(fout);
    return 0;
}

