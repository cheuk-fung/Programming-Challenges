#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *fin, *fout;

int fav[110];
int mxcnt[110];
int unsure[110];
int ans[110];

int main()
{
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    int m, k;
    fscanf(fin, "%d%d", &m, &k);
    for (int i = 0; i < k; i++) {
        int d;
        fscanf(fin, "%d", &d);
        fav[d] = 1;
    }

    int n;
    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++) {
        int d;
        fscanf(fin, " %*s %d", &d);
        for (int j = 0; j < d; j++) {
            int b;
            fscanf(fin, "%d", &b);
            if (b) {
                if (fav[b]) mxcnt[i]++;
            } else {
                unsure[i]++;
            }
        }
        int rem = m - k - (d - unsure[i] - mxcnt[i]);
        if (unsure[i] > rem) {
            mxcnt[i] += unsure[i] - rem;
            unsure[i] = rem;
        }
        if (unsure[i] > k - mxcnt[i]) unsure[i] = k - mxcnt[i];
    }

    int mx = max_element(mxcnt, mxcnt + n) - mxcnt;
    memset(ans, 0xff, sizeof ans);
    bool surely = true;
    for (int i = 0; i < n; i++) {
        if (mxcnt[i] == mxcnt[mx]) continue;
        if (mxcnt[i] + unsure[i] < mxcnt[mx]) ans[i] = 1;
        else if (mxcnt[i] + unsure[i] == mxcnt[mx]) ans[i] = 2;
        else {
            ans[i] = 2;
            surely = false;
        }
    }
    if (surely) {
        int cnt = count(mxcnt, mxcnt + n, mxcnt[mx]);
        if (cnt > 1) {
            int last = -1;
            for (int i = 0; i < n; i++) {
                if (ans[i] != -1) continue;
                if (unsure[i] != 0) {
                    surely = false;
                    if (last == -1) last = i;
                    else last = -2;
                }
            }
            if (last >= 0) ans[last] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) continue;
        ans[i] = surely ? 0 : 2;
    }

    for (int i = 0; i < n; i++) fprintf(fout, "%d\n", ans[i]);

    return 0;
}

