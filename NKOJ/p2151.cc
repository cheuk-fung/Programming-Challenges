/*
 *  SRC: NKOJ
 * TASK: 細胞分裂
 * ALGO: NULL
 * DATE: 03/22/2011 
 *
 * Created by Leewings Ac
 */

#include	<cstdio>
#include	<cmath>
#include	<climits>

using namespace std;

int prime(int* p, int* sp, int m)
{
    int b[m + 1], total = 0;
    for (int i = 0; i <= m; i++) b[i] = 1;
    for (int i = 2; i <= m; i++)
        if (b[i]) {
            if (m % i == 0) {
                p[total] = i;

                int t_m = m;
                sp[total] = 0;
                while (t_m % i == 0) {
                    sp[total]++;
                    t_m /= i;
                }
                total++;
            }
            for (int j = i; j <= m; j += i) b[j] = 0;
        }

    return total;
}

int main()
{
    int n, m1, m2;
    scanf("%d%d%d", &n, &m1, &m2);
    int s[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &s[i]);

    int p[m1 + 1], sp[m1 + 1];
    int total = prime(p, sp, m1);

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        int t_ans = 0;
        for (int j = 0; j < total; j++) {
            if (s[i] % p[j]) {
                t_ans = INT_MAX;
                break;
            }
            int k = 0, t_s = s[i];
            while (t_s % p[j] == 0) {
                k++;
                t_s /= p[j];
            }
            int time = sp[j] * m2 / k;
            if (time * k - sp[j] * m2) time++;
            if (time > t_ans) t_ans = time;
        }
        if (t_ans < ans) ans = t_ans;
    }

    if (ans == INT_MAX) printf("-1\n");
    else printf("%d\n", ans);

    return 0;
}				/* ----------  end of function main  ---------- */
