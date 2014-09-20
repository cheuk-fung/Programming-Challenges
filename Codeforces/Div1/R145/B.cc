#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, tot, h[300];
int f[40010][2];

int work(int a, int b)
{
    int res = INF;
    for (int i = a; i >= 0 && tot - i <= b; i--) {
        res = min(res, min(f[i][0], f[i][1]));
    }

    return res;
}

FILE *fin, *fout;

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    int a, b;
    fscanf(fin, "%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        fscanf(fin, "%d", h + i);
        tot += h[i];
    }

    memset(f, 0x3f, sizeof f);
    f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = max(a, b); j >= h[i]; j--) {
            f[j][1] = min(f[j][1], f[j][0] + min(h[i], h[i - 1]));
            f[j][0] = min(f[j - h[i]][0], f[j - h[i]][1] + min(h[i], h[i - 1]));
        }
        for (int j = h[i] - 1; j >= 0; j--) {
            f[j][1] = min(f[j][1], f[j][0] + min(h[i], h[i - 1]));
            f[j][0] = INF;
        }
    }

    int r1 = work(a, b);
    int r2 = work(b, a);
    int ans = min(r1, r2);
    fprintf(fout, "%d\n", ans == INF ? -1 : ans);

    return 0;
}

