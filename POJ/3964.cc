/*
 *  SRC: POJ 3964
 * PROB: Factorial Simplification
 * ALGO: Number Theory
 * DATE: Oct 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAX_PRM = 100000;

int n, m, ans_cnt;
int pi[1024], qi[1024];
int r[1024], s[1024];
int prm_cnt, prm[MAX_PRM];
bool is_prm[MAX_PRM];
int prm_sum[MAX_PRM], tmp_sum[MAX_PRM];

int get_prm(int n, int *p, bool *b)
{
    int cnt = 0;
    memset(b, true ,sizeof(bool) * n);
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

void divide(int n, int coef, int *sum)
{
    for (int i = 0; i < prm_cnt && n >= prm[i]; i++) {
        int a = n;
        while (a > 1) {
            a /= prm[i];
            sum[i] += a * coef;
        }
    }
}

bool check(int p)
{
    memset(tmp_sum, 0, sizeof(tmp_sum));
    divide(p, 1, tmp_sum);
    for (int i = 0; i < prm_cnt; i++)
        if (prm_sum[i] < tmp_sum[i]) return false;
    return true;
}

bool bisection()
{
    int left = 1, right = MAX_PRM;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    if (left == 1) return false;
    
    memset(tmp_sum, 0, sizeof(tmp_sum));
    divide(left, 1, tmp_sum);

    r[ans_cnt] = left;
    int min_s = 0x3fffffff;
    for (int i = 0; i < prm_cnt; i++) {
        if (tmp_sum[i] && prm_sum[i] / tmp_sum[i] < min_s)
            min_s = prm_sum[i] / tmp_sum[i];
    }
    s[ans_cnt++] = min_s;

    for (int i = 0; i < prm_cnt; i++)
        prm_sum[i] -= tmp_sum[i] * min_s;

    return true;
}

int main()
{
    prm_cnt = get_prm(MAX_PRM, prm, is_prm);

    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", pi + i);
        divide(pi[i], 1, prm_sum);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", qi + i);
        divide(qi[i], -1, prm_sum);
    }

    for (int i = 0; i < prm_cnt; i++)
        if (prm_sum[i] < 0) {
            puts("-1");
            return 0;
        }

    while (bisection()) ;

    if (!ans_cnt) puts("0");
    else {
        printf("%d\n", ans_cnt);
        for (int i = 0; i < ans_cnt; i++)
            printf("%d %d\n", r[i], s[i]);
    }

    return 0;
}
