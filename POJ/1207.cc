/*
 *  SRC: POJ 1207
 * PROB: The 3n + 1 problem
 * ALGO: NULL
 * DATE: Nov 27, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

int solve(int n)
{
    int s = 1;
    while (n != 1) {
	if (n % 2) n = 3 * n + 1;
	else n /= 2;
	s++;
    }
    return s;
}

int main()
{
    for (int i, j; scanf("%d %d", &i, &j) == 2; ) {
	int max = 0, a, b;
	if (i < j) {
	    a = i;
	    b = j;
	}
	else {
	    a = j;
	    b = i;
	}
	for (int k = a; k <= b; k++) {
	    int tmp = solve(k);
	    max = max > tmp ? max : tmp;
	}
	printf("%d %d %d\n", i, j, max);
    }

    return 0;
}

