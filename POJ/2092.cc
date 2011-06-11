/*
 *  SRC: POJ
 * TASK: Grandpa is Famous
 * ALGO: NULL
 * DATE: Dec. 12, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

bool solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0) return false;

    int rank[10001], first = 0, second = 0;
    for (int i = 0; i < 10001; i++) rank[i] = 0;

    for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++) {
	    int tmp;
	    scanf("%d", &tmp);
	    rank[tmp]++;
	}

    for (int i = 0; i < 10001; i++)
	if (rank[i] > first) {
	    second = first;
	    first = rank[i];
	}
	else if (rank[i] < first && rank[i] > second)
	    second = rank[i];

    int k;
    for (k = 0; k < 10001; k++)
	if (rank[k] == second) {
	    printf("%d", k);
	    break;
	}
    for (k++; k < 10001; k++)
	if (rank[k] == second) printf(" %d", k);
    printf("\n");

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}

