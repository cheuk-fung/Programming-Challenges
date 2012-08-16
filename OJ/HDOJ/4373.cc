/*
 *  SRC: HDOJ 4373
 * PROB: Mysterious For
 * ALGO: Number Theory
 * DATE: Aug 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 2000010;
const int MOD = 364875103;

int prmcnt, prm[MAXN], cnt[MAXN];
bool isprm[MAXN];

int prime(int n, int *p, bool *b)
{
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }
    return cnt;
}

long long divide(int n, int k)
{
    memset(cnt, 0, sizeof(cnt));

    long long res = 1;
    for (int i = 0; i < prmcnt && n >= prm[i]; i++) {
        int a = n, b = k, c = n - k;

        while (a > 1) {
            a /= prm[i];
            cnt[i] += a;
        }

        while (b > 1) {
            b /= prm[i];
            cnt[i] -= b;
        }

        while (c > 1) {
            c /= prm[i];
            cnt[i] -= c;
        }

        for (int j = 0; j < cnt[i]; j++) {
            res = res * prm[i] % MOD;
        }
    }
    return res;
}

int pos[20];

int main()
{
    prmcnt = prime(MAXN, prm, isprm);

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case #%d: ", task);

        int n, m;
        scanf("%d%d", &n, &m);
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d", pos + i);
        }
        pos[k] = m;

        long long ans = 1;
        for (int i = 1; i <= k; i++) {
            ans = ans * divide(n + (pos[i] - pos[i - 1]) - 1, pos[i] - pos[i - 1]) % MOD;
        }

        cout << ans << endl;
    }

    return 0;
}

