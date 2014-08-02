/*
 *  SRC: NKOJ 1597
 * PROB: Prime Land
 * ALGO: Prime
 * DATE: Aug 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAX_N = 32768;

int get_prime(int n, int* p, bool* b)
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

int prm[3512];
bool is_prm[MAX_N];
char end;

struct Node {
    int p, e;
} ans[100];

int mypow(int p, int e)
{
    int res = 1;
    for (int i = 0; i < e; i++) res *= p;
    return res;
}

inline int next_int()
{
    int res = 0;
    while ((end = getchar()) != ' ' && end != '\n')
        res = res * 10 + end - '0';
    return res;
}

int main()
{
    get_prime(MAX_N, prm, is_prm);

    while (1 + 1 == 2) {
        int p = next_int();
        if (!p) break;
        int e = next_int(),
            num = mypow(p, e);

        while (end != '\n') {
            p = next_int();
            e = next_int();
            num *= mypow(p, e);
        }

        num--;
        int cnt = 0, prm_i = 0;
        while (num > 1) {
            ans[cnt].p = prm[prm_i];
            ans[cnt].e = 0;
            while (num % prm[prm_i] == 0) {
                ans[cnt].e++;
                num /= prm[prm_i];
            }
            prm_i++;
            if (ans[cnt].e) cnt++;
        }

        for (int i = cnt - 1; i > 0; i--) printf("%d %d ", ans[i].p, ans[i].e);
        printf("%d %d\n", ans[0].p, ans[0].e);
    }

    return 0;
}
