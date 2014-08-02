#include <cstdio>
#include <cstring>

const int MAXPRM = 100000;

int prmcnt;
int prm[MAXPRM];
bool isprm[MAXPRM];

int get_prm(int n, int *p, bool *b)
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

bool check(int num)
{
    for (int i = 0; i < prmcnt && prm[i] <= num; i++) {
        if (num % prm[i] == 0) {
            num /= prm[i];
            if (num < MAXPRM) {
                if (isprm[num]) {
                    return true;
                }
                return false;
            }
            for (int j = 0; j < prmcnt && prm[j] <= num; j++) {
                if (num % prm[j] == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    prmcnt = get_prm(MAXPRM, prm, isprm);

    int n;
    scanf("%d", &n);
    while (n--) {
        int num;
        scanf("%d", &num);
        if (check(num)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

    return 0;
}
