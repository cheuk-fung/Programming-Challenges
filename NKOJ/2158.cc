/*
 *  SRC: NKOJ
 * TASK: Fantastic Problem from Sheldon
 * ALGO: NULL
 * DATE: 03/30/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>

const long MAXN = 100000;

struct Star {
    long t, s;
} star[MAXN];

inline long max(long a, long b)
{
    return a > b ? a : b;
}

int main()
{
    long N;
    long long ans = 0;
    scanf("%ld", &N);
    for (long i = 0; i < N; i++) {
        scanf("%ld%ld", &star[i].t, &star[i].s);
        for (long j = 0; j < i; j++) {
            ans += max(star[i].t - star[j].t, star[i].s - star[j].s);
            ans += max(star[j].t - star[i].t, star[j].s - star[i].s);
        }
    }

    printf("%lld\n", ans);

    return 0;
}				/* ----------  end of function main  ---------- */

