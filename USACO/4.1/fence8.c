/*
ID: os.idea1
LANG: C
TASK: fence8
*/
#include <stdio.h>

FILE *fin, *fout;

long N, R, board[50], rail[1024], cut_from[1024], tb, tr;

void swap(long *a, long *b)
{
    long tmp = *a;
    *a = * b;
    *b = tmp;
}

void quick_sort(long a[], long l, long r)
{
    long i = l, j = r, mid = a[(l + r) / 2];
    while (i < j)
    {
	while (a[i] < mid) i++;
	while (a[j] > mid) j--;
	if (i <= j) swap(&a[i++], &a[j--]);
    }
    if (i < r) quick_sort(a, i, r);
    if (j > l) quick_sort(a, l, j);
}

int Impossible()
{
    long i, waste = 0;
    for (i = 0; i < N; i++)
	if (board[i] < rail[0]) waste += board[i];
    if (waste > tb - tr) return 1;
    return 0;
}

int dfs(long p)
{
    if (p == -1) return 1;
    if (Impossible()) return 0;
    long j, low = 0;
    if (rail[p] == rail[p + 1]) low = cut_from[p + 1];
    for (j = N - 1; j >= low; j--)
	if (board[j] >= rail[p])
	{
	    cut_from[p] = j;
	    board[j] -= rail[p];
	    if (dfs(p - 1)) 
	    {
		board[j] += rail[p];
		return 1;
	    }
	    board[j] += rail[p];
	}
    return 0;
}

int main()
{
    fin = fopen("fence8.in", "r");
    fout = fopen("fence8.out", "w");

    fscanf(fin, "%ld", &N);
    long i;
    for (i = 0; i < N; i++) 
    {
	fscanf(fin, "%ld", &board[i]);
	tb += board[i];
    }
    quick_sort(board, 0, N - 1);
    fscanf(fin, "%ld", &R);
    for (i = 0; i < R; i++) fscanf(fin, "%ld", &rail[i]);
    quick_sort(rail, 0, R - 1);

    long l = 0, r = R;
    while (l + 1 != r)
    {
	long mid = (l + r) / 2;
	for (i = 0, tr = 0; i < mid; i++) tr += rail[i];
	if (dfs(mid - 1)) l = mid;
	else r = mid;
    }

    for (i = 0, tr = 0; i < r; i++) tr += rail[i];
    if (dfs(r - 1))
	fprintf(fout, "%ld\n", r); 
    else
	fprintf(fout, "%ld\n", l);

    fclose(fin); fclose(fout);
    return 0;
}
