/*
ID: os.idea1
LANG: C
TASK: msquare
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
int tms[8], multi[10], used[40321], goal;

struct DATA
{
    int ms[8], pre, f;
    char abc;
}data[40321];

int npr(int mms[8])
{
    int i, j, k, hash[9], p = 0;
    memset(hash, 0, sizeof(hash));
    //long long p = 1;
    for (i = 7; i >= 0; i--)
    {	
	hash[mms[i]] = 1; k = 0;
	for (j = 1; j < mms[i]; j++)
	    if (!hash[j]) k++;
	p += multi[i] * k;
    }


	//p = p * 10 + mms[i];
	//p += multi[i] * (mms[i] - 1);
    //return p % 139759;
    return p;
}

void prepare()
{
    int i;
    for (i = 0; i < 8; i++)
	fscanf(fin, "%d", &tms[i]);
    multi[0] = 1;
    for (i = 1; i < 10; i++)
	multi[i] = multi[i - 1] * i;
    goal = npr(tms);
    printf("%d\n", goal);
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int write(int q)
{
    if (data[q].pre >= 0)
    {
	int i = write(data[q].pre);
	if (i > 0 && i % 60 == 0) fprintf(fout, "\n");
	fprintf(fout, "%c", data[q].abc);
	return i + 1;
    }
    return 0;
}

int checkused(struct DATA p, int q, char c)
{
    int pp = npr(p.ms);
    if (pp == goal)
    {
	fprintf(fout, "%d\n", p.f);
	int i = write(q);
	if (i > 0 && i % 60 == 0) fprintf(fout, "\n");
	fprintf(fout, "%c\n", c);
	return 2;
    }
    if (used[pp]) return 0;
    else 
    {
	used[pp] = 1;
	return 1;
    }
}

void search()
{
    int open = 0, closed = -1, i, j;
    for (i = 0; i < 8; i++)
	data[0].ms[i] = i + 1;
    data[0].pre = -1; data[0].f = 0;
    if (npr(data[0].ms) == goal)
    {
	fprintf(fout, "0\n\n");
	return;
    }
    i = checkused(data[0], closed, 'a');
    while (closed < open)
    {
	struct DATA tmp = data[++closed];
	tmp.pre = closed; tmp.f = data[closed].f + 1;
	for (i = 0; i < 4; i++)
	    swap(&tmp.ms[i], &tmp.ms[7 - i]);
	j = checkused(tmp, closed, 'A');
	if (j == 2) return;
	if (j)
	{
	    tmp.abc = 'A';
	    data[++open] = tmp;
	}

	tmp = data[closed];
	tmp.pre = closed; tmp.f = data[closed].f + 1;
	for (i = 0; i < 3; i++)
	{
	    swap(&tmp.ms[i], &tmp.ms[3]);
	    swap(&tmp.ms[7 - i], &tmp.ms[4]);
	}
	j = checkused(tmp, closed, 'B');
	if (j == 2) return;
	if (j)
	{
	    tmp.abc = 'B';
    	    data[++open] = tmp;
	}

    	tmp = data[closed];
	tmp.pre = closed; tmp.f = data[closed].f + 1;
	swap(&tmp.ms[1], &tmp.ms[2]);
	swap(&tmp.ms[1], &tmp.ms[5]);
	swap(&tmp.ms[1], &tmp.ms[6]);
	j = checkused(tmp, closed, 'C');
	if (j == 2) return;
	if (j)
	{
	    tmp.abc = 'C';
	    data[++open] = tmp;
	}
    }
}

int main()
{
    fin = fopen("msquare.in", "r");
    fout = fopen("msquare.out", "w");

    prepare();
    search();
    /*
    int mmm[8];
    for (mmm[0] = 1; mmm[0] <= 8; mmm[0]++)
    for (mmm[1] = 1; mmm[1] <= 8; mmm[1]++)
	if (mmm[0]!=mmm[1])
    for (mmm[2] = 1; mmm[2] <= 8; mmm[2]++)
	if (mmm[0]!=mmm[2] && mmm[1]!=mmm[2])
    for (mmm[3] = 1; mmm[3] <= 8; mmm[3]++)
	if (mmm[0]!=mmm[3] && mmm[1]!=mmm[3] && mmm[2]!=mmm[3])
    for (mmm[4] = 1; mmm[4] <= 8; mmm[4]++)
	if (mmm[0]!=mmm[4] && mmm[1]!=mmm[4] && mmm[2]!=mmm[4] && mmm[3]!=mmm[4])
    for (mmm[5] = 1; mmm[5] <= 8; mmm[5]++)
	if (mmm[0]!=mmm[5] && mmm[1]!=mmm[5] && mmm[2]!=mmm[5] && mmm[3]!=mmm[5] && mmm[4]!=mmm[5])
    for (mmm[6] = 1; mmm[6] <= 8; mmm[6]++)
	if (mmm[0]!=mmm[6] && mmm[1]!=mmm[6] && mmm[2]!=mmm[6] && mmm[3]!=mmm[6] && mmm[4]!=mmm[6] && mmm[5]!=mmm[6])
    for (mmm[7] = 1; mmm[7] <= 8; mmm[7]++)
	if (mmm[0]!=mmm[7] && mmm[1]!=mmm[7] && mmm[2]!=mmm[7] && mmm[3]!=mmm[7] && mmm[4]!=mmm[7] && mmm[5]!=mmm[7] && mmm[6]!=mmm[7])
    {
	int pp = npr(mmm);
	printf("%d ", pp);int i;
	    for (i = 0; i < 8; i++)
		printf("%d ", mmm[i]);
	    printf("\n");
	if (used[pp])
	{
	    
	    getchar();
	}
	else
	    used[pp] = 1;
    }*/
 	

    fclose(fin); fclose(fout);
    return 0;
}
