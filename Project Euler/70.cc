#include <cstdio>
#include <cstring>

const int UPPER_BOUND = 10000000;
int prm[UPPER_BOUND], phi[UPPER_BOUND];
bool is_prm[UPPER_BOUND];

int get_prime(int n, int *prm, bool *is_prm)
{
    memset(is_prm, true, sizeof(bool) * n);
    is_prm[0] = is_prm[1] = false;

    int cnt = 0;
    for (int i = 2; i < n; i++) {
        if (is_prm[i]) prm[cnt++] = i;
        for (int j = 0; j < cnt && i * prm[j] < n; j++) {
            is_prm[i * prm[j]] = false;
            if (i % prm[j] == 0) break;
        }
    }

    return cnt;
}

void eulers_phi(int n, int *phi, int prm_cnt, int *prm)
{
    phi[1] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < prm_cnt && i * prm[j] < n; j++) {
            if (i % prm[j] == 0) {
                phi[i * prm[j]] = phi[i] * prm[j];
                break;
            } else {
                phi[i * prm[j]] = phi[i] * (prm[j] - 1);
            }
        }
    }
}

bool is_permutation(int x, int y)
{
    int cnt[10] = {0};
    while (x) {
        cnt[x % 10]++;
        x /= 10;
    }
    while (y) {
        cnt[y % 10]--;
        y /= 10;
    }
    for (int i = 0; i < 10; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int prm_cnt = get_prime(UPPER_BOUND, prm, is_prm);
    eulers_phi(UPPER_BOUND, phi, prm_cnt, prm);

    int min_n = 2;
    double min_phi = 2.0 / phi[2];
    for (int i = 3; i < UPPER_BOUND; i++) {
        if (is_permutation(i, phi[i]) && (double) i / phi[i] < min_phi) {
            min_n = i;
            min_phi = (double) i / phi[i];
        }
    }
    printf("%d %f\n", min_n, min_phi);

    return 0;
}
