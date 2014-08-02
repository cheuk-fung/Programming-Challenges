/*
 *  SRC: ZOJ 3518
 * PROB: Unsafe Factor
 * ALGO: NULL
 * DATE: Oct 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

bool p[10000010];
pii A[100010];

void run(int n)
{
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &A[i].first, &A[i].second);
        A[i].second++;
    }
    sort(A, A + n);
    for (int i = 0, x = 0; i < n; i++) {
        for (x = max(x, A[i].first); x < A[i].second; x++) {
            p[x] ^= 1;
        }
    }
}

int main()
{
    int L, n1, n2;
    while (~scanf("%d%d%d", &L, &n1, &n2)) {
        memset(p, 0, sizeof p);
        run(n1);
        run(n2);

        int ans = 0;
        int x = 0, pre = -1;
        for ( ; x < L; x++) {
            if (!p[x]) {
                ans = max(ans, x - 1 - pre);
                pre = x;
            }
        }
        ans = max(ans, x - 1 - pre);
        printf("%d\n", ans);
    }

    return 0;
}

