/*
 *  SRC: NKOJ
 * TASK: Crazy Review
 * ALGO: Greedy
 * DATE: 03/27/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>

int main()
{
    long N, H;
    scanf("%ld%ld", &N, &H);
    long S[N], V[N], Dv[N], U[N];
    for (long i = 0; i < N; i++)
        scanf("%ld%ld%ld%ld", &S[i], &V[i], &Dv[i], &U[i]);

    for (long i = 0; i < N; i++) {
        while (S[i] < 60) {
            if (H && V[i]) {
                H--;
                S[i] += V[i] < U[i] - S[i] ? V[i] : U[i] - S[i];
                V[i] += Dv[i];
                if (V[i] <= 0 || S[i] == U[i]) V[i] = Dv[i] = 0;
            }
            else {
                printf("POOR SWEETSC\n");
                return 0;
            }
        }
    }

    while (H) {
        long maxV = 0, maxI = -1;
        for (long i = 0; i < N; i++) {
            if (V[i] > maxV && U[i] - S[i] > maxV) {
                maxV = V[i] < U[i] - S[i] ? V[i] : U[i] - S[i];
                maxI = i;
            }
        }
        if (maxI > -1) {
            H--;
            S[maxI] += maxV;
            V[maxI] += Dv[maxI];
            if (V[maxI] <= 0 || S[maxI] == U[maxI]) V[maxI] = Dv[maxI] = 0;
        }
        else break;
    }

    long total = 0;
    for (long i = 0; i < N; i++) total += S[i];

    printf("%ld\n", long(float(total) / float(N) + 0.5));

    return 0;
}				/* ----------  end of function main  ---------- */

