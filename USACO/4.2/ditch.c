/*
ID: os.idea1
LANG: C
TASK: ditch
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

FILE *fin, *fout;

long n, m, E = 201, F, src, dest;
long head[500], d[500], place[500], q[500];

struct EDGE
{
    long st, ed, capa, flow, next;
} edge[500];

long min(long a, long b)
{
    return a < b ? a : b;
}

void add_edge(long u, long v, long c)
{
    edge[E].st = u; edge[E].ed = v;
    edge[E].capa = c;
    edge[E].next = head[u];
    head[u] = E;

    long tE = 400 - E++;
    edge[tE].st = v; edge[tE].ed = u;
    edge[tE].capa = 0;
    edge[tE].next = head[v];
    head[v] = tE;
}

long BFS()
{
    memset(d, -1, sizeof(d));

    long open = 0, closed = -1;
    q[0] = src; d[src] = 0;
    while (closed < open)
    {
	long e = head[q[++closed]];
	while (e != -1)
	{
	    if (d[edge[e].ed] == -1 && edge[e].flow < edge[e].capa)
	    {
		d[edge[e].ed] = d[q[closed]] + 1;
		q[++open] = edge[e].ed;
	    }
	    e = edge[e].next;
	}
    }
    return d[dest] >= 0;
}

long DFS(long s, long f)
{
    if (s == dest) return f;
    long delta = 0, e = place[s];
    while (e != -1)
    {
	if (d[edge[e].ed] == d[s] + 1 && edge[e].flow < edge[e].capa)
	{
	    long tmp = DFS(edge[e].ed, min(f - delta, edge[e].capa - edge[e].flow));
	    delta += tmp;
	    edge[e].flow += tmp;
	    edge[400 - e].flow = -edge[e].flow;
	    if (delta == f) break;
	}
	e = edge[e].next;
    }
    place[s] = e;
    return delta;
}

int main()
{
    fin = fopen("ditch.in", "r");
    fout = fopen("ditch.out", "w");

    fscanf(fin, "%ld %ld", &n, &m);

    src = 201; dest = m + 200;
    memset(head, -1, sizeof(head));

    long i;
    for (i = 0; i < n; i++)
    {
	long u, v, c;
	fscanf(fin, "%ld %ld %ld", &u, &v, &c);
	add_edge(u + 200, v + 200, c);
    }

    long t;
    while (BFS())
    {
	for (i = 0; i < E; i++) place[i] = head[i];
	t = DFS(src, LONG_MAX);
	if (t) F += t;
	else break;
    }

    fprintf(fout, "%ld\n", F);

    fclose(fin); fclose(fout);
    return 0;
}
