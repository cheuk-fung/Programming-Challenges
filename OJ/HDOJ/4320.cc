/*
 *  SRC: HDOJ 4320
 * PROB: Arcane Numbers 1
 * ALGO: Math
 * DATE: Jul 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXP = 1000100;
int prm[MAXP];
bool is_prm[MAXP];

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

int main()
{
    int prmcnt = get_prime(MAXP, prm, is_prm);

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        long long a, b;
        cin >> a >> b;
        while (a <= 0 || b <= 0) ;
        printf("Case #%d: ", task);
        bool flag = true;
        for (int i = 0; i < prmcnt && prm[i] <= a; i++) {
            if (a % prm[i] == 0) {
                if (b % prm[i]) {
                    flag = false;
                    break;
                }
                while (a % prm[i] == 0) {
                    a /= prm[i];
                }
            }
        }
        if (b % a) flag = false;
        if (flag) {
            puts("YES");
        } else {
            puts("NO");
        }
    }

    return 0;
}
