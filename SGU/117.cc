#include <cstdio>
#include <cstring>

const int MAXN = 10010;

int prmcnt, prm[MAXN];
bool isprm[MAXN];

int kcnt[MAXN], cnt[MAXN];

int getprm(int n, int *p, bool *b)
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

void getcnt(int k, int *cnt)
{
    memset(cnt, 0, sizeof(int) * prmcnt);
    for (int i = 0; i < prmcnt && prm[i] <= k; i++) {
        while (k % prm[i] == 0) {
            cnt[i]++;
            k /= prm[i];
        }
    }
}

int main(int argc, char *argv[])
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    prmcnt = getprm(MAXN, prm, isprm);

    int ans = 0;
    getcnt(k, kcnt);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        getcnt(a, cnt);
        bool ok = true;
        for (int i = 0; i < prmcnt; i++) {
            if (kcnt[i] && cnt[i] * m < kcnt[i]) {
                ok = false;
                break;
            }
        }
        ans += ok;
    }

    printf("%d\n", ans);

    return 0;
}
