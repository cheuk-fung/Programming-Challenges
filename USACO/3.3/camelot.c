/*
ID: os.idea1
LANG: C
TASK: camelot
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

FILE *fin, *fout;

int R, C, pk, pking, ans = INT_MAX;
short used[50][50], d[50][50][50][50], dist[50][50], kingdist[50][50];

struct point
{
    int x, y;
} king[9], kn[1000];

struct DATA
{
    int s, f, x, y;
} data[1000];

static int sun[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}},
	   ks[8][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};

void init()
{
    fin = fopen("camelot.in", "r");
    fout = fopen("camelot.out", "w");

    fscanf(fin, "%d %d\n", &R, &C);

    fscanf(fin, "%c %d\n", &king[0].x, &king[0].y);
    king[0].x -= 'A' - 1;
    int i;
    for (i = 0; i < 8; i++)
	if (king[0].x + ks[i][0] > 0 && king[0].x + ks[i][0] <= C
		&& king[0].y + ks[i][1] > 0 && king[0].y + ks[i][1] <= R)
	{
	    king[++pking].x = king[0].x + ks[i][0];
	    king[pking].y = king[0].y + ks[i][1];
	}

    while (1 + 1 == 2)
    {
	if (feof(fin)) break;
	fscanf(fin, "%c", &kn[pk].x);
	while (kn[pk].x == ' ')
	    fscanf(fin, "%c", &kn[pk].x);
	if (kn[pk].x == '\n') continue;
	kn[pk].x -= 'A' - 1;
	fscanf(fin, "%d", &kn[pk++].y);
    }
}

void BFSkn(int x, int y)
{
    int open = 0, closed = -1;
    data[0].s = 0; data[0].f = -1;
    data[0].x = x; data[0].y = y;
    memset(used, 0, sizeof(used));
    used[x][y] = 1;
    while (closed < open)
    {
	struct DATA tmp = data[++closed];
	int i;
	for (i = 0; i < 8; i++)
	    if (tmp.x + sun[i][0] > 0 && tmp.x + sun[i][0] <= C
		    && tmp.y + sun[i][1] > 0 && tmp.y + sun[i][1] <= R
		    && !used[tmp.x + sun[i][0]][tmp.y + sun[i][1]])
	    {
		used[tmp.x + sun[i][0]][tmp.y + sun[i][1]] = 1;
		data[++open] = tmp;
		data[open].x = tmp.x + sun[i][0];
		data[open].y = tmp.y + sun[i][1];
		data[open].s = data[closed].s + 1;
		data[open].f = closed;
		if (d[x][y][data[open].x][data[open].y] == -1)
		    d[x][y][data[open].x][data[open].y]++; 
		d[x][y][data[open].x][data[open].y] += data[open].s;
	    }
    }
}

void BFSking(int x, int y)
{
    int open = 0, closed = -1;
    data[0].s = 0; data[0].f = -1;
    data[0].x = x; data[0].y = y;
    memset(used, 0, sizeof(used));
    used[x][y] = 1;
    while (closed < open)
    {
	struct DATA tmp = data[++closed];
	int i;
	for (i = 0; i < 8; i++)
	    if (tmp.x + ks[i][0] > 0 && tmp.x + ks[i][0] <= C
		    && tmp.y + ks[i][1] > 0 && tmp.y + ks[i][1] <= R
		    && !used[tmp.x + ks[i][0]][tmp.y + ks[i][1]])
	    {
		used[tmp.x + ks[i][0]][tmp.y + ks[i][1]] = 1;
		data[++open] = tmp;
		data[open].x = tmp.x + ks[i][0];
		data[open].y = tmp.y + ks[i][1];
		data[open].s = data[closed].s + 1;
		data[open].f = closed;
		kingdist[data[open].x][data[open].y] += data[open].s;
	    }
    }
}

void distcalc()
{
    int i, j, k;
    for (i = 1; i <= C; i++)
	for (j = 1; j <= R; j++)
	{
	    for (k = 0; k < pk; k++)
	    {
		if (d[kn[k].x][kn[k].y][i][j] == -1)
		{
		    dist[i][j] = -1;
		    break;
		}
		dist[i][j] += d[i][j][kn[k].x][kn[k].y];		
	    }
	}
}

void Dcalc()
{
    int i, j, k, l, tmp, tans;
    for (i = 1; i <= C; i++)
	for (j = 1; j <=R; j++)
	{
	    if (dist[i][j] == -1) continue;
	    for (k = 0; k < pk; k++)
	    {
		tmp = dist[i][j] - d[kn[k].x][kn[k].y][i][j];
		if (tmp >= ans) continue;
		for (l = 0; l < pking; l++)
		{
		    if (d[kn[k].x][kn[k].y][king[l].x][king[l].y] == -1 || d[king[l].x][king[l].y][i][j] == -1) continue;
		    tans = tmp + d[kn[k].x][kn[k].y][king[l].x][king[l].y] + d[king[l].x][king[l].y][i][j] + (l ? 1 : 0);
		    ans = ans < tans ? ans : tans;
		}
	    }
	    tans = dist[i][j] + kingdist[i][j];
	    ans = ans < tans ? ans : tans;
	}
}

int main()
{
    init();

    int i, j;
    memset(d, -1, sizeof(d));
    for (i = 1; i <= C; i++)
	for (j = 1; j <= R; j++)
	{
	    d[i][j][i][j] = 0;
	    BFSkn(i, j);
	}
    BFSking(king[0].x, king[0].y);

    distcalc();
    Dcalc();

    fprintf(fout, "%d\n", ans);

    fclose(fin); fclose(fout);
    return 0;
}
