/*
ID: os.idea1
LANG: C
TASK: shuttle
*/
#include <stdio.h>

FILE *fin, *fout;

long n;

int main()
{
    fin = fopen("shuttle.in", "r");
    fout = fopen("shuttle.out", "w");

    fscanf(fin, "%ld", &n);

    long i, j, k, sum = 1;
    for (i = 2; i <= n + 1; i++)
    {
	if (i % 2)
	    for (j = 0, k = n + i; j < i; j++, k -= 2)
	    {
		fprintf(fout, "%ld", k);
		if (sum % 20 == 0) fprintf(fout, "\n");
		else fprintf(fout, " ");
		sum++;
	    }
	else
	    for (j = 0, k = n - i + 2; j < i; j++, k += 2)
	    {
		fprintf(fout, "%ld", k);
		if (sum % 20 == 0) fprintf(fout, "\n");		
		else fprintf(fout, " ");
		sum++;
	    }
    }
    for (i = n; i > 1; i--)
    {
	if (i % 2)
	    for (j = 0, k = n + i; j < i; j++, k -= 2)
	    {
		fprintf(fout, "%ld", k);
		if (sum % 20 == 0) fprintf(fout, "\n");		
		else fprintf(fout, " ");
		sum++;
	    }
	else
	    for (j = 0, k = n - i + 2; j < i; j++, k += 2)
	    {
		fprintf(fout, "%ld", k);
		if (sum % 20 == 0) fprintf(fout, "\n");		
		else fprintf(fout, " ");
		sum++;
	    }
    }
    fprintf(fout, "%ld\n", n + 1);
	    
    fclose(fin); fclose(fout);
    return 0;
}
