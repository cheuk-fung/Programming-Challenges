#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXNUM = 1e7 + 10;
const int MAXPRM = 1e5 + 10;
const int MAXN = 1e5 + 10;

int prmcnt, prm[MAXPRM];
bool isprm[MAXPRM];

int a[MAXN], b[MAXN];
int pa[MAXNUM], pb[MAXNUM];

int getprm(int n, int *p, bool *b)
{
    int cnt = 0;
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * prm[j] < n; j++) {
            b[i * prm[j]] = false;
            if (i % prm[j] == 0) break;
        }
    }
    return cnt;
}

void factorize(int *p, int n)
{
    for (int i = 0; i < prmcnt && prm[i] * prm[i] <= n; i++) {
        if (n % prm[i] == 0) {
            while (n % prm[i] == 0) {
                n /= prm[i];
                p[prm[i]]++;
            }
        }
    }
    if (n > 1) p[n]++;
}

int divide(int *p, int n)
{
    int r = n;
    for (int i = 0; i < prmcnt && prm[i] * prm[i] <= n; i++) {
        if (n % prm[i] == 0) {
            while (n % prm[i] == 0) {
                n /= prm[i];
                if (p[prm[i]]) {
                    r /= prm[i];
                    p[prm[i]]--;
                }
            }
        }
    }
    if (n > 1 && p[n]) {
        r /= n;
        p[n]--;
    }
    return r;
}

int main()
{
    prmcnt = getprm(MAXPRM, prm, isprm);

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < m; i++) scanf("%d", b + i);
    for (int i = 0; i < n; i++) factorize(pa, a[i]);
    for (int i = 0; i < m; i++) factorize(pb, b[i]);
    for (int i = 0; i < MAXNUM; i++) pa[i] = pb[i] = min(pa[i], pb[i]);

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) printf("%d ", divide(pa, a[i]));
    putchar(10);
    for (int i = 0; i < m; i++) printf("%d ", divide(pb, b[i]));
    putchar(10);

    return 0;
}
