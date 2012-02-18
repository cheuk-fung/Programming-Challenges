#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 1e7;
int prm_cnt;
int prm[MAXN];
bool is_prm[MAXN];

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
    long long q;
    cin >> q;
    prm_cnt = get_prime(MAXN, prm, is_prm);

    for (int i = 0; i < prm_cnt; i++) {
        if (q % prm[i] == 0) {
            if (q == prm[i]) break;
            q /= prm[i];
            for (int j = i; j < prm_cnt; j++) {
                if (q % prm[j] == 0) {
                    if (q == prm[j]) break;
                    cout << 1 << endl;
                    cout << (long long)prm[i] * prm[j] << endl;
                    return 0;
                }
            }
            cout << 2 << endl;
            return 0;
        }
    }
    cout << 1 << endl << 0 << endl;

    return 0;
}

