/*
ID: os.idea1
LANG: C
TASK: lgame
*/
#include <stdio.h>
#include <string.h>

FILE *fin, *fout, *dict;

const long v[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

long  maxv, pd, pans, dv[400000], ssum[26], dsum[26];
char s[15], sd[15], d[400000][15], ans[40000][15];

void quick_sort(long l, long r)
{
    long i = l, j = r;
    char mid[15], tmp[15];
    memcpy(mid, ans[(l + r) /2], sizeof(ans[(l + r) / 2]));
    while (i < j)
    {
	while (strcmp(ans[i], mid) < 0) i++;	
	while (strcmp(ans[j], mid) > 0) j--;
	if (i <= j)
	{
	    memcpy(tmp, ans[i], sizeof(ans[i]));
	    memcpy(ans[i], ans[j], sizeof(ans[j]));
	    memcpy(ans[j], tmp, sizeof(tmp));
	    i++; j--;
	}
	if (i < r) quick_sort(i, r);
	if (l < j) quick_sort(l, j);
    }
}

int main()
{
    fin = fopen("lgame.in", "r");
    fout = fopen("lgame.out", "w");
    dict = fopen("lgame.dict", "r");

    long i;
    fscanf(fin, "%s", s);
    for (i = 0; i < strlen(s); i++)
	ssum[s[i] - 'a']++;

    fscanf(dict, "%s", sd);
    while (sd[0] != '.')
    {
	long sv = 0;
	memset(dsum, 0, sizeof(dsum));
	for (i = 0; i < strlen(sd); i++)
	{
	    dsum[sd[i] - 'a']++;
	    sv += v[sd[i] - 'a'];
	}
	for (i = 0; i < 26; i++)
	    if (dsum[i] > ssum[i]) break;
	if (i != 26)
	{
	    fscanf(dict, "%s", sd);
	    continue;
	}
	if (sv > maxv)  maxv = sv;
	dv[pd] = sv;
	memcpy(d[pd++], sd, sizeof(sd));
	fscanf(dict, "%s", sd);
    }

    long j, k;
    for (i = 0; i < pd; i++)
	for (j = i + 1; j <= pd; j++)
	    if (dv[i] + dv[j] >= maxv)
	    {
		memset(dsum, 0, sizeof(dsum));
		for (k = 0; k < strlen(d[i]); k++)
		    dsum[d[i][k] - 'a']++;
		for (k = 0; k < strlen(d[j]); k++)
		    dsum[d[j][k] - 'a']++;
		for (k = 0; k < 26; k++)
		    if (dsum[k] > ssum[k]) break;
		if (k != 26) continue;
		if (dv[i] + dv[j] > maxv)
		{
		    maxv = dv[i] + dv[j];
		    pans = 0;
		    memset(ans, 0, sizeof(ans));
		}
		if (j == pd)
		{
		    memcpy(ans[pans++], d[i], sizeof(d[i]));
		    continue;
		}
		if (strcmp(d[i], d[j]) < 0)
		{
		    memcpy(ans[pans], d[i], sizeof(d[i]));
		    strcat(ans[pans], " ");
		    strcat(ans[pans], d[j]);
		}
		else
		{
		    memcpy(ans[pans], d[j], sizeof(d[j]));
		    strcat(ans[pans], " ");
		    strcat(ans[pans], d[i]);
		}
		pans++;
	    }

    fprintf(fout, "%ld\n", maxv);
    quick_sort(0, pans - 1);
    for (i = 0; i < pans; i++)
	fprintf(fout, "%s\n", ans[i]);

    fclose(fin); fclose(fout);
    return 0;
}
