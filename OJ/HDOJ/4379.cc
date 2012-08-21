/*
 *  SRC: HDOJ 4379
 * PROB: The More The Better
 * ALGO: NULL
 * DATE: Aug 21, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

inline int MAX(int x, int y) { return x > y ? x : y; }
inline int MIN(int x, int y) { return x < y ? x : y; }

int main()
{
    int n, L, A, B, mod;
    while (~scanf("%d%d%d%d%d", &n, &L, &A, &B, &mod)) {
        A *= 2;
        B *= 2;
        mod *= 2;

        int cnt = 0;
        int left = 0, right = -1;
        for (int i = 1; i <= n; i++) {
            int x = (1ll * A * i + B) % mod;
            if (x <= L) {
                cnt++;
                left = MAX(x, left);
            } else {
                right = right == -1 ? x : MIN(x, right);
            }
        }
        if (right != -1 && (long long)left + right <= 2ll * L) cnt++;
        printf("%d\n", cnt);
    }

    return 0;
}

