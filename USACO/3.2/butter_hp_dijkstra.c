/*
ID: os.idea1
LANG: C
TASK: butter
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "math.h"

FILE *fin, *fout;

long n, m, c;
long cowtot[1000], map[1000][1000], edge[1000][1000];
long min = LONG_MAX;
long d[1000], hash[1000], heap[1000], heap_size;

void init()
{
    fin = fopen("butter.in", "r");
    fout = fopen("butter.out", "w");

    fscanf(fin, "%ld %ld %ld", &n, &m, &c);

    long i;
    for (i = 0; i < n; i++)
    {
	long j;
	fscanf(fin, "%ld", &j);
	cowtot[j - 1]++;
    }

    for (i = 0; i < c; i++)
    {
	long a, b, c;
	fscanf(fin, "%ld %ld %ld", &a, &b, &c);
	a--, b--;
	edge[a][++edge[a][0]] = b;
	edge[b][++edge[b][0]] = a;
	map[a][b] = map[b][a] = c;
    }
}

void swap(long *a, long *b)
{
    long tmp = *a;
    *a = *b;
    *b = tmp;   
}  

void heap_down(long i)
{
    while (i < (heap_size >> 1))
    {
	long j = (i << 1) + 1;
	if (j + 1 < heap_size && d[heap[j + 1]] < d[heap[j]]) j++;
	if (d[heap[j]] < d[heap[i]])
	{
	    swap(&heap[i], &heap[j]);
	    hash[heap[i]] = i;
	    hash[heap[j]] = j;
	    i = j;
	}
	else
	{
	    break;
	}
    }
}

void heap_up(long i)
{
    while (i)
    {
	long j = (i - 1) >> 1;
	if (d[heap[i]] < d[heap[j]])
	{
	    swap(&heap[i], &heap[j]);
	    hash[heap[i]] = i;
	    hash[heap[j]] = j;
	    i = j;
	}
	else
	{
	    break;
	}
    }
}

long heap_pop()
{
    long top = heap[0];
    heap[0] = heap[--heap_size];
    hash[heap[0]] = 0;
    heap_down(0);

    return top;
}

void dijkstra(long p)
{
    long i;
    for (i = 0; i < m; i++)
	d[i] = LONG_MAX;
    d[p] = 0;

    for (i = 1; i <= edge[p][0]; i++)
	d[edge[p][i]] = map[p][edge[p][i]];

    heap_size = 0;
    for (i = 0; i < m; i++)
    {
	heap[heap_size] = i;
	hash[i] = heap_size++;
    }

    for (i = (heap_size >> 1) - 1; i >= 0; i--)
	heap_down(i);

    while (heap_size)
    {
	long q = heap_pop();

	for (i = 1; i <= edge[q][0]; i++)
	{
	    if (d[q] + map[q][edge[q][i]] < d[edge[q][i]])
	    {
		d[edge[q][i]] = d[q] + map[q][edge[q][i]];
		heap_up(hash[edge[q][i]]);
	    }
	}
    }

    long tot = 0;
    for (i = 0; i < m; i++)
	if (cowtot[i])
	{
	    tot += d[i] * cowtot[i];
	}

    min = min < tot? min : tot;
}

void work()
{
    long i;
    for (i = 0; i < m; i++)
	dijkstra(i);
}

void writeln()
{
    fprintf(fout, "%ld\n", min);
    printf("%ld\n", min);
}

void fileclose()
{
    fclose(fin);
    fclose(fout);
}

int main()
{
    init();

    work();

    writeln();

    fileclose();

    return 0;
}

