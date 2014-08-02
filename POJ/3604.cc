/*
 *  SRC: POJ 3604
 * PROB: Professor Ben
 * ALGO: Number Theory
 * DATE: Aug 01, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int prmCnt, prm[500];
bool isPrm[2500];

int getPrime(int n, int* p, bool* b)
{
    int cnt = 0;
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return cnt;
}

int main()
{
    getPrime(2500, prm, isPrm);
    
    int CASE;
    scanf("%d", &CASE);
    while (CASE--) {
        int n;
        scanf("%d", &n);

        long long ans = 1;
        for (int i = 0; prm[i] * prm[i] <= n; i++) {
            int cnt = 0;
            while (n % prm[i] == 0) {
                cnt++;
                n /= prm[i];
            }
            ans *= (cnt + 1LL) * (cnt + 2LL) * (cnt + 1LL) * (cnt + 2LL) / 4LL;
        }

        printf("%lld\n", ans * (n > 1 ? 9 : 1));
    }

    return 0;
}
