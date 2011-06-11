/*
 *  SRC: POJ 1007
 * PROB: DNA Sorting
 * ALGO: stable sort
 * DATE: Dec 11, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct DNA {
    char* str;
    int num;
};

bool cmp(DNA a, DNA b)
{
    return a.num < b.num;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    DNA dna[m];
    for (int i = 0; i < m; i++) {
	dna[i].str = new char[n + 1];
	dna[i].num = 0;
	scanf("%s", dna[i].str);
	for (int j = 0; j < n; j++)
	    for (int k = j + 1; k < n; k++)
		if (dna[i].str[j] > dna[i].str[k]) dna[i].num++;
    }

    stable_sort(dna, dna + m, cmp);

    for (int i = 0; i < m; i++)
	printf("%s\n", dna[i].str);

    return 0;
}

