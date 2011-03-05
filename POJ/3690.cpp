/*
 *  SRC: POJ
 * TASK: Constellations
 * ALGO: KMP
 * DATE: Dec. 12, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

long long two[51];

inline void calcTwo()
{
    two[0] = 1;
    for (int i = 1; i < 51; i++)
	two[i] = two[i - 1] << 1;
}

inline long long calc(char* s, int len)
{
    long long res = 0;
    for (int i = 0; i < len; i++)
	if (*s++ == '*') res += two[i];
    return res;
}

void KMPInit(int P[], long long B[], int m)
{
    P[0] = -1;
    for (int i = 1, j = -1; i < m; i++) {
	while (j > -1 && B[j + 1] != B[i]) j = P[j];
	if (j < m - 1 && B[j + 1] == B[i]) j++;
	P[i] = j;
    }
}

int KMP(int P[], long long A[], long long B[], int n, int m)
{
    int res = 0;

    for (int i = 0, j = -1; i < n; i++) {
	while (j > -1 && B[j + 1] != A[i]) j = P[j];
	if (j < m - 1 && B[j + 1] == A[i]) j++;
	if (j == m - 1) {
	    res++;
	    j = P[j];
	}
    }

    return res;
}

bool solve()
{
    int n, m, t, p, q;
    scanf("%d %d %d %d %d", &n, &m, &t, &p, &q);
    if (!(n && m && t && p && q)) return false;

    char sky[n][m + 1];
    for (int i = 0; i < n; i++)
	scanf("%s", sky[i]);

    long long cons[t][p];
    for (int k = 0; k < t; k++)
	for (int i = 0; i < p; i++) {
	    char tmp[q + 1];
	    scanf("%s", tmp);
	    cons[k][i] = calc(tmp, q);
	}

    int P[t][p];
    for (int k = 0; k < t; k++) KMPInit(P[k], cons[k], p);

    int ans = 0;
    long long map[n];
    for (int j = 0; j < m - q + 1; j++) {
	if (!j)
	    for (int i = 0; i < n; i++) map[i] = calc(sky[i], q);
	else
	    for (int i = 0; i < n; i++) {
		map[i] >>= 1;
		if (sky[i][j + q - 1] == '*') map[i] += two[q - 1];
	    }

	for (int k = 0; k < t; k++) ans += KMP(P[k], map, cons[k], n, p); 
    }
 
    static int Case;
    printf("Case %d: %d\n", ++Case, ans);

    return true;
}

int main()
{
    calcTwo();

    while (solve()) ;

    return 0;
}

