/*
 *  SRC: NKOJ
 * TASK: Erase the word
 * ALGO: KMP
 * DATE: 03/28/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<cstring>

inline void KMPInit(long* P, char* B, long m)
{
    P[0] = -1;
    for (long i = 1, j = -1; i < m; i++) {
	while (j > -1 && B[j + 1] != B[i]) j = P[j];
	if (B[j + 1] == B[i]) j++;
	P[i] = j;
    }
}

inline long KMP(long* P, char* A, char* B, long n, long m)
{
    long res = 0, t_j[2000], pt_j = 0;

    for (long i = 0, j = -1; i < n; i++) {
	while (j > -1 && B[j + 1] != A[i]) j = P[j];
	if (B[j + 1] == A[i]) j++;
	if (j == m - 1) {
	    res++;
            pt_j -= m;
            j = t_j[pt_j % 2000];
	}
        t_j[pt_j++ % 2000] = j;
    }

    return res;
}

int main()
{
    char w[2000], s[200000];
    scanf("%s", w);
    scanf("%s", s);

    long P[2000];
    KMPInit(P, w, strlen(w));
    printf("%ld\n", KMP(P, s, w, strlen(s), strlen(w)));

    return 0;
}				/* ----------  end of function main  ---------- */

