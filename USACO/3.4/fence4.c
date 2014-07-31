/*
ID: os.idea1
LANG: C
TASK: fence4
*/
#include <stdio.h>

FILE *fin, *fout;

int n, cansee[201];
double sx, sy;

struct POINT
{
    double x, y;
} p[201];

int side(double ax, double ay, double bx, double by, double cx, double cy)
{
    double x = bx - ax, y = by - ay,
	   Xx = cx - ax, Yy = cy - ay,
	   t = x * Yy - y * Xx;
    if (t > 1e-5) return 1; // t > 0
    if (t < -1e-5) return 2; // t < 0
    return 0;
}

int intersect(int a, int b)
{
    if (side(p[a].x, p[a].y, p[a + 1].x, p[a + 1].y, p[b].x, p[b].y) == side(p[a].x, p[a].y, p[a + 1].x, p[a + 1].y, p[b + 1].x, p[b + 1].y))
	return 0;
    if (side(p[b].x, p[b].y, p[b + 1].x, p[b + 1].y, p[a].x, p[a].y) == side(p[b].x, p[b].y, p[b + 1].x, p[b + 1].y, p[a + 1].x, p[a + 1].y))
	return 0;
    return 1;
}

int check_side()
{
    int i, j;
    for (i = 0; i < n; i++)
	for (j = i + 2; j < n; j++)
	{
	    if (i == 0 && j == n - 1) continue;
	    if (intersect(i, j)) return 0;
	}
    return 1;
}

int get_see(int mx, int my)
{
    int k, canseek = n;
    double min, ml, mr;
    min = ml = mr = 1e10;

    for (k = 0; k < n; k++)
    {
	double t = (mx - sx) * (p[k + 1].y - p[k].y) - (my - sy) * (p[k + 1].x - p[k].x);
	if (t < 1e-5 && t > -1e-5) continue; // t == 0

	double a = (p[k].x - sx) * (p[k + 1].y - p[k].y) - (p[k].y - sy) * (p[k + 1].x - p[k].x),
	       b = (mx - sx) * (p[k + 1].y - p[k].y) - (my - sy) * (p[k + 1].x - p[k].x);
	if (b < 1e-5 && b > -1e-5) // b == 0
	{
	    if (p[k + 1].x - p[k].x < 1e-5 && p[k + 1].x - p[k].x > -1e-5) // p[k + 1].x - p[k].x == 0
	    {
		a = p[k].x - sx;
		b = mx - sx;
	    }
	    else // p[k + 1].y - p[k].y == 0
	    {
		a = p[k].y - sy;
		b = my - sy;
	    }
	}
	double i = a / b;
	if (i < -1e-5) continue; // i < 0
	if (p[k + 1].x - p[k].x < 1e-5 && p[k + 1].x - p[k].x > -1e-5) // p[k + 1].x - p[k].x == 0
	{
	    a = sy + (my - sy) * i - p[k].y;
	    b = p[k + 1].y - p[k].y;
	}
	else // p[k + 1].y - p[k].y == 0
	{
	    a = sx + (mx - sx) * i - p[k].x;
	    b = p[k + 1].x - p[k].x;
	}
	double j = a / b;
	if (j < -1e-5 || j > 1 + 1e-5) continue; // j < 0 || j > 1

	double x = sx + (mx - sx) * i,
	       y = sy + (my - sy) * i;
	t = (x - sx) * (x - sx) + (y - sy) * (y - sy);

	if (t < -1e-5 || t >= min) continue; // t < 0 || t > min

	if (j < 1e-5 || j > 1 - 1e-5) // j == 0 || j == 1
	{
	    int t1, t2;
	    if (j < 1e-5) // j == 0
	    {
		t1 = k - 1, t2 = k + 1;
		if (t1 < 0) t1 += n;
	    }
	    else // j == 1
	    {
		t1 = k, t2 = k + 2;
		if (t2 > n) t2 -= n;
	    }

	    int s1 = side(sx, sy, mx, my, p[t1].x, p[t1].y),
		s2 = side(sx, sy, mx, my, p[t2].x, p[t2].y);
	    if (s1 == s2)
	    {
		if (s1 == 1 && t < ml) ml = t;
		if (s1 == 2 && t < mr) mr = t;
		continue;
	    }
	}

	min = t;
	canseek = k;
    }

    if (min > ml && min > mr) return n;
    return canseek;
}

int main()
{
    fin = fopen("fence4.in", "r");
    fout = fopen("fence4.out", "w");

    fscanf(fin, "%d %lf %lf", &n, &sx, &sy);
    int i;
    for (i = 0; i < n; i++)
	fscanf(fin, "%lf %lf", &p[i].x, &p[i].y);
    p[n].x = p[0].x;
    p[n].y = p[0].y;

    if (check_side())
	for (i = 0; i < n; i++)
	{
	    cansee[get_see(p[i].x, p[i].y)] = 1;
	    cansee[get_see((p[i].x + p[i + 1].x) / 2, (p[i].y + p[i + 1].y) / 2)] = 1;
	}
    else
	fprintf(fout, "NOFENCE\n");

    int tot = 0;
    for (i = 0; i < n; i++)
	if (cansee[i]) tot++;
    fprintf(fout, "%d\n", tot);

    for (i = 0; i < n - 2; i++)
	if (cansee[i])
	    fprintf(fout, "%.0f %.0f %.0f %.0f\n", p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
    if (cansee[n - 1])
	fprintf(fout, "%0.f %0.f %0.f %0.f\n", p[0].x, p[0].y, p[n - 1].x, p[n - 1].y);
    if (cansee[n - 2])
	fprintf(fout, "%0.f %0.f %0.f %0.f\n", p[n - 2].x, p[n - 2].y, p[n - 1].x, p[n - 1].y);

    fclose(fin); fclose(fout);
    return 0;
}
