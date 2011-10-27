/*
ID: os.idea1
LANG: C
TASK: nuggets
*/
#include <stdio.h>

FILE *fin, *fout;

long n, box[10], f[256 * 256], ans, max1, max2;

long get_gcd(int a, int b)
{
    if (!b) return a;
    return get_gcd(b, a % b);
}

int main()
{
    fin = fopen("nuggets.in", "r");
    fout = fopen("nuggets.out", "w");

    fscanf(fin, "%ld", &n);
    long i, j;
    for (i = 0; i < n; i++)
    {
	fscanf(fin, "%ld", &box[i]);

	if (box[i] == 1 || n == 1)
	{
	    fprintf(fout, "0\n");
	    fclose(fin); fclose(fout);
	    return 0;
	}

	if (box[i] > max1)
	{
	    max2 = max1;
	    max1 = box[i];
	}
	if (box[i] < max1 && box[i] > max2) max2 = box[i];
	
	f[box[i] % 256] = 1;
    }

    long gcd = get_gcd(box[0], box[1]);
    for (i = 2; i < n; i++)
	gcd = get_gcd(gcd, box[i]);

    if (gcd != 1)
    {
	fprintf(fout, "0\n");
	fclose(fin); fclose(fout);
	return 0;
    }

    long LIMIT = max1 * max2 / get_gcd(max1, max2);
    for (i = 0; i <= LIMIT; i++)
    {
	for (j = 0; j < n; j++)
	    if (i - box[j] >= 0 && f[i - box[j]])
	    {
		f[i] = 1;
		break;
	    }
	if (!f[i]) ans = i;
    }

    fprintf(fout, "%ld\n", ans);

    fclose(fin); fclose(fout);
    return 0;
}
