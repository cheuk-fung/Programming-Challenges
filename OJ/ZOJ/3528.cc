/*
 *  SRC: ZOJ 3528
 * PROB: Parterre
 * ALGO: NULL
 * DATE: Oct 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

int mat[555][555], col[555];
int vis[555], sum[555];

inline int count(int a, int b, int c, int d)
{
    return min(b, d) - max(a, c) + 1;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        int loops = (min(n, m) + 1) >> 1;
        for (int i = 0; i < loops; i++) {
            scanf("%d", col + i);
            for (int j = i; j <= m - 1 - i; j++) mat[i][j] = i;
            for (int j = i; j <= n - 1 - i; j++) mat[j][m - 1 - i] = i;
            for (int j = m - 1 - i; j >= i; j--) mat[n - 1 - i][j] = i;
            for (int j = n - 1 - i; j >= i; j--) mat[j][i] = i;
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int T, L, B, R;
            scanf("%d%d%d%d", &T, &L, &B, &R);

            memset(vis, 0, sizeof vis);
            for (int i = L; i <= R; i++) {
                vis[mat[T][i]] = 1;
                vis[mat[B][i]] = 1;
            }
            for (int i = T; i <= B; i++) {
                vis[mat[i][L]] = 1;
                vis[mat[i][R]] = 1;
            }
            if (T <= loops - 1 && loops - 1 <= B) {
                for (int i = L; i <= R; i++) {
                    vis[mat[loops - 1][i]] = 1;
                }
            }
            if (L <= loops - 1 && loops - 1 <= R) {
                for (int i = T; i <= B; i++) {
                    vis[mat[i][loops - 1]] = 1;
                }
            }

            memset(sum, 0, sizeof sum);
            for (int i = 0; i < loops; i++) {
                if (vis[i]) {
                    if (i == n - 1 - i) {
                        sum[col[i]] += count(L, R, i, m - 1 - i);
                    } else if (i == m - 1 - i) {
                        sum[col[i]] += count(T, B, i, n - 1 - i);
                    } else {
                        if (T <= i && i <= B) {
                            sum[col[i]] += count(L, R, i, m - 1 - i);
                        }
                        if (L <= m - 1 - i && m - 1 - i <= R) {
                            sum[col[i]] += count(T, B, i, n - 1 - i);
                        }
                        if (T <= n - 1 - i && n - 1 - i <= B) {
                            sum[col[i]] += count(L, R, i, m - 1 - i);
                        }
                        if (L <= i && i <= R) {
                            sum[col[i]] += count(T, B, i, n - 1 - i);
                        }
                        if (T <= i && i <= B && L <= i && i <= R) sum[col[i]]--;
                        if (T <= i && i <= B && L <= m - 1 - i && m - 1 - i <= R) sum[col[i]]--;
                        if (T <= n - 1 - i && n - 1 - i <= B && L <= m - 1 - i && m - 1 - i <= R) sum[col[i]]--;
                        if (T <= n - 1 - i && n - 1 - i <= B && L <= i && i <= R) sum[col[i]]--;
                    }
                }
            }

            int TOTAL = 0, INDEX, COUNT = 0;
            for (int i = 1; i <= 250; i++) {
                if (sum[i] != 0) {
                    TOTAL++;
                    if (sum[i] > COUNT) {
                        INDEX = i;
                        COUNT = sum[i];
                    }
                }
            }
            printf("%d %d %d\n", TOTAL, INDEX, COUNT);
        }
    }

    return 0;
}

