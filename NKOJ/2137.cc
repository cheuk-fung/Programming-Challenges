/*
 *  SRC: NKOJ 2137
 * PROB: Divisible Subsumuences
 * ALGO: Math
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

long long sum[50000];
int mod_cnt[1000001];

inline long long comb(long long n)
{
    return n * (n - 1) / 2;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);

    while (jobs--) {
        int d, n;
        scanf("%d%d", &d, &n);
        scanf("%lld", sum);
        for (int i = 1; i < n; i++) {
            scanf("%lld", sum + i);
            sum[i] += sum[i - 1];
        }

        int max_mod = 0;
        for (int i = 0; i < n; i++) {
            int tmp = sum[i] % d;
            mod_cnt[tmp]++;
            if (tmp > max_mod) max_mod = tmp;
        }
            
        long long cnt = mod_cnt[0];
        for (int i = 0; i <= max_mod; i++) {
            if (mod_cnt[i] > 1) cnt += comb(mod_cnt[i]);
            mod_cnt[i] = 0;
        }
       printf("%lld\n", cnt); 
    }

    return 0;
}
