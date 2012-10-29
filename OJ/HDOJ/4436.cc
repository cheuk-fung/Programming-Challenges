/*
 *  SRC: HDOJ 4436
 * PROB: str2int
 * ALGO: Suffix Array
 * DATE: Oct 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

enum {
    MOD = 2012,
    MAXN = 111010
};

class Suffix_Array {
    private:
        enum {
            MAXLEN = 111010,
            MAXCHAR = 11000
        };

        int *nrank;
        int rbuf[2][MAXLEN], cnt[MAXLEN];

        void csort(int k, int range)
        {
            int t = 0;
            for (int i = len - k; i < len; i++) nrank[t++] = i;
            for (int i = 0; i < len; i++)
                if (suff[i] >= k) nrank[t++] = suff[i] - k;

            for (int i = 0; i < len; i++) cnt[rank[i]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1, j; i >= 0; i--) {
                j = nrank[i];
                suff[--cnt[rank[j]]] = j;
            }
            memset(cnt, 0, sizeof(int) * range);
        }

    public:
        int str[MAXLEN];
        int len;
        int suff[MAXLEN], hgt[MAXLEN];
        int *rank;

        void reset()
        {
            len = 0;
            memset(rbuf, 0, sizeof rbuf);
            memset(cnt, 0, sizeof cnt);
            memset(suff, 0, sizeof suff);
            memset(hgt, 0, sizeof hgt);
        }

        void build()
        {
            rank = rbuf[0];
            nrank = rbuf[1];
            for (int i = 0; i < len; i++) {
                rank[i] = str[i];
                suff[i] = i;
            }
            csort(0, MAXCHAR);

            for (int k = 1, maxrank = MAXCHAR; maxrank != len; k <<= 1) {
                csort(k, maxrank + 1);
                maxrank = nrank[suff[0]] = 1;
                for (int i = 1; i < len; i++) {
                    if (rank[suff[i - 1]] == rank[suff[i]] && rank[suff[i - 1] + k] == rank[suff[i] + k]) {
                        nrank[suff[i]] = maxrank;
                    } else {
                        nrank[suff[i]] = ++maxrank;
                    }
                }
                swap(rank, nrank);
            }
            for (int i = 0; i < len; i++) rank[i]--;

            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = rank[i] ? suff[rank[i] - 1] : len; str[i + k] == str[j + k]; k++)
                    ;
        }
} sa;

char str[MAXN];
int f[MAXN], g[MAXN];
int last[MAXN], ten[MAXN];

int main()
{
    ten[0] = 1;
    for (int i = 1; i < MAXN; i++) ten[i] = (ten[i - 1] * 10) % MOD;
    for (int i = 1; i < MAXN; i++) ten[i] = (ten[i - 1] + ten[i]) % MOD;

    int n;
    while (~scanf("%d", &n)) {
        sa.reset();

        for (int i = 0, delim = 60; i < n; i++) {
            scanf("%s", str);
            char *s = str;
            while (*s) sa.str[sa.len++] = *s++;
            last[i] = sa.len;
            sa.str[sa.len++] = delim++;
        }
        sa.build();

        f[0] = g[0] = 0;
        for (int i = 1; i <= sa.len; i++) {
            if (sa.str[i - 1] > '9') {
                f[i] = g[i] = 0;
            } else {
                f[i] = (f[i - 1] * 10 + sa.str[i - 1] - '0') % MOD;
                g[i] = (g[i - 1] + f[i]) % MOD;
            }
        }

        int sum = 0;
        for (int i = 0; i < sa.len; i++) {
            if (sa.str[sa.suff[i]] == '0') continue;
            if (sa.str[sa.suff[i]] >= 60) break;
            int r = *upper_bound(last, last + n, sa.suff[i]);
            int l = sa.suff[i] + sa.hgt[i];
            if (l >= r) continue;
            sum = ((sum + (g[r] - g[l] - f[sa.suff[i]] * (ten[r - l + sa.hgt[i]] - ten[sa.hgt[i]]))) % MOD + MOD) % MOD;
        }
        printf("%d\n", sum);
    }

    return 0;
}

