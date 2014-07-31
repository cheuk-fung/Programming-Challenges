/*
ID: os.idea1
LANG: C
TASK: cowcycle
*/
#include <stdio.h>
#include <float.h>
#include <string.h>

FILE *fin, *fout;

long F, R, F1, F2, R1, R2;
long double fs[100], rs[100], af[100], ar[100];
long double sum[3500], bit[3500];
long double v = FLT_MAX; //variance

void calc()
{
    //if ((fs[F - 1] / rs[0]) / (fs[0] / rs[R - 1]) < (long double)3) return;
    if (fs[F - 1] * rs[R - 1] < 3 * (rs[0] * fs[0])) return;
    long i, j, k, l, pk = 0;
    for (i = 0; i < F; i++)
	for (j = 0; j < R; j++)
	{
	    long double tmp = fs[i] / rs[j];
	    for (k = 0; k < pk; k++)
	    {
		if (tmp > bit[k])
		{
		    for (l = pk; l > k; l--) bit[l] = bit[l - 1];
		    break;
		}
	    }
	    bit[k] = tmp;
	    pk++;
	}
    long double aver = 0, tot = 0;
    for (i = 0; i < pk - 1; i++)
    {
	sum[i] = bit[i] - bit[i + 1];
	aver += sum[i];
    }
    aver /= F * R - 1;
    for (i = 0; i < pk - 1; i++)
	tot += (sum[i] - aver) * (sum[i] - aver);
    if (tot < v)
    {
	v = tot;
	memcpy(af, fs, sizeof(fs));
	memcpy(ar, rs, sizeof(rs));
    }
}

void search(long pre, long d, long fr)
{
    if (!fr) //F
    {
	if (d == F)
	{
	    search(R1, 0, 1);
	    return;
	}
	long i;
	for (i = pre; i <= F2 - (F - 1 - d); i++)
	{
	    fs[d] = (long double)i;
	    search(i + 1, d + 1, 0);
	}
    }
    else //R
    {
	if (d == R)
	{
	    calc();
	    return;
	}
	long i;
	for (i = pre; i <= R2 - (R - 1 - d); i++)
	{
	    rs[d] = (long double)i;
	    search(i + 1, d + 1, 1);
	}
    }
}

int main()
{
    fin = fopen("cowcycle.in", "r");
    fout = fopen("cowcycle.out", "w");

    fscanf(fin, "%ld %ld %ld %ld %ld %ld", &F, &R, &F1, &F2, &R1, &R2);

    search(F1, 0, 0);

    long i;
    for (i = 0; i < F - 1; i++) fprintf(fout, "%.0Lf ", af[i]);
    fprintf(fout, "%.0Lf\n", af[i]);
    for (i = 0; i < R - 1; i++) fprintf(fout, "%.0Lf ", ar[i]);
    fprintf(fout, "%.0Lf\n", ar[i]);

    fclose(fin); fclose(fout);
    return 0;
}
