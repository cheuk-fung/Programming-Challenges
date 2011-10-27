/*
ID: os.idea1
LANG: C
TASK: telecow
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

FILE *fin, *fout;

long N, M, src, dest, E = 2001, F;
long head[4000], place[4000], d[4000], q[4000];
long vis[4000], used[4000];

struct EDGE
{
    long st, ed;
    long capa, flow;
    long next;
} edge[4000];

long min(long a, long b)
{
    return a < b ? a : b;
}

void add_edge(long u, long v, long c)
{
    edge[E] = (struct EDGE){u, v, c, 0, head[u]};
    head[u] = E;

    edge[4000 - E] = (struct EDGE){v, u, 0, 0, head[v]};
    head[v] = 4000 - E++;
}

int BFS()
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
    return d[dest] > -1;
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
	    edge[4000 - e].flow = -edge[e].flow;
	    if (delta == f) break;
	}
	e = edge[e].next;
    }
    place[s] = e;
    return delta;
}

void flood_fill(long p)
{
    long i;
    for (i = 4000 - E; i < E; i++)
	if (edge[i].st == p && !used[i] && edge[i].flow < edge[i].capa)
	{
	    vis[edge[i].ed] = 1;
	    used[i] = 1;
	    flood_fill(edge[i].ed);
	}
}

int main()
{
    fin = fopen("telecow.in", "r");
    fout = fopen("telecow.out", "w");

    long s, t;
    fscanf(fin, "%ld %ld %ld %ld", &N, &M, &s, &t);
    src = (s << 1) - 1; dest = t << 1;

    memset(head, -1, sizeof(head));
    
    long i;
    for (i = 1; i <= N; i++) 
    {
	if (i == s)
	    add_edge(src, src + 1, LONG_MAX);
	else if (i == t)
	    add_edge(dest - 1, dest, LONG_MAX);
	else
	    add_edge((i << 1) - 1, i << 1, 12001 + i);
    }
    for (i = 0; i < M; i++)
    {
	long a, b;
	fscanf(fin, "%ld %ld", &a, &b);
	a = (a << 1) - 1; b = (b << 1) - 1;
	add_edge(a + 1, b, LONG_MAX);
	add_edge(b + 1, a, LONG_MAX);
    }

    while (BFS())
    {
	memcpy(place, head, sizeof(head));
	long t = DFS(src, LONG_MAX);
	if (t) F += t;
	else break;
    }

    fprintf(fout, "%ld\n", F / 12001);
    vis[src] = 1; vis[src + 1] = 1;
    flood_fill(src + 1);
    vis[dest] = 0; vis[dest - 1] = 0;

    long first = 1;
    for (i = 2001; i < E; i++)
	if (vis[edge[i].st] && !vis[edge[i].ed])
	{
	    if (first)
	    {
		fprintf(fout, "%ld", (edge[i].st + 1) >> 1);
		first = 0;
	    }
	    else
	    	fprintf(fout, " %ld", (edge[i].st + 1) >> 1);
	}
    fprintf(fout, "\n");

    fclose(fin); fclose(fout);
    return 0;
}
