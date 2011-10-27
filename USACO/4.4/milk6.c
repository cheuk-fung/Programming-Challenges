/*
ID: os.idea1
LANG: C
TASK: milk6
*/
#include <stdio.h>
#include <string.h>

#define MAXN 1000

const long long LLONG = 1 << 30;

FILE *fin, *fout;
long N, M, E = MAXN + 1, src, dest;
long long F;
long head[MAXN * 3], d[MAXN * 3], place[MAXN * 3], q[MAXN * 3];
long vis[MAXN * 3], used[MAXN * 3];

struct EDGE
{
    long st, ed;
    long long capa, flow;
    long next;
} edge[MAXN * 3];

long long min(long long a, long long b)
{
    return a < b ? a : b;
}

void add_edge(long u, long v, long long c)
{
    edge[E] = (struct EDGE){u, v, c, 0, head[u]};
    head[u] = E;

    edge[MAXN * 2 - E] = (struct EDGE){v, u, 0, 0, head[v]};
    head[v] = MAXN * 2 - E++;
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

long long DFS(long s, long long f)
{
    if (s == dest) return f;
    long long delta = 0;
    long e = place[s];
    while (e != -1)
    {
	if (d[edge[e].ed] == d[s] + 1 && edge[e].flow < edge[e].capa)
	{
	    long long tmp = DFS(edge[e].ed, min(f - delta, edge[e].capa - edge[e].flow));
	    delta += tmp;
	    edge[e].flow += tmp;
	    edge[MAXN * 2 - e].flow = -edge[e].flow;
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
    for (i = MAXN * 2 - E; i < E; i++)
	if (edge[i].st == p && !used[i] && edge[i].flow < edge[i].capa)
	{
	    vis[edge[i].ed] = 1;
	    used[i] = 1;
	    flood_fill(edge[i].ed);
	}
}

int main()
{
    fin = fopen("milk6.in", "r");
    fout = fopen("milk6.out", "w");

    fscanf(fin, "%ld %ld", &N, &M);

    src = MAXN + 1; dest = N + MAXN;
    memset(head, -1, sizeof(head));

    long i;
    for (i = 0; i < M; i++)
    {
	long u, v, c;
	fscanf(fin, "%ld %ld %ld", &u, &v, &c);
	add_edge(u + MAXN, v + MAXN, c * (MAXN + 1) + 1);
    }

    while (BFS())
    {
	for (i = 0; i < E; i++) place[i] = head[i];
	long long t = DFS(src, LLONG);
	if (t) F += t;
	else break;
    }

    fprintf(fout, "%ld %ld\n", (long)(F / (MAXN + 1)), (long)(F % (MAXN + 1)));

    vis[src] = 1;
    flood_fill(src);

    for (i = MAXN + 1; i < E; i++)
	if (vis[edge[i].st] && !vis[edge[i].ed])
	{
	    if (head[i] < MAXN && edge[i].next < MAXN && edge[i].ed != dest)
	    {
		long j;
		for (j = MAXN + 1; j < i; j++)
		    if (edge[j].st == edge[i].ed && !vis[edge[j].ed])
		    {
			vis[edge[i].ed] = 1;
			i = MAXN;
			break;
		    }
	    }
	    else fprintf(fout, "%ld\n", i - MAXN);
	}

    fclose(fin); fclose(fout);
    return 0;
}
