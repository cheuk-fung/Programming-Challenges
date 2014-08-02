/*
 *  SRC: HDOJ 3948
 * PROB: The Number of Palindromes
 * ALGO: Suffix Array
 * DATE: Oct 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

class Suffix_Array {
    private:
        enum {
            MAXLEN = 100010 << 1,
            MAXCHAR = 256
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
        char str[MAXLEN];
        int len;
        int suff[MAXLEN], hgt[MAXLEN];
        int mnhgt[20][MAXLEN];
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
                        nrank[suff[i]] = ++ maxrank;
                    }
                }
                swap(rank, nrank);
            }
            for (int i = 0; i < len; i++) rank[i]--;
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = rank[i] ? suff[rank[i] - 1] : len; str[i + k] == str[j + k]; k++)
                    ;
        }

        void calc_lcp()
        {
            memcpy(mnhgt[0], hgt, sizeof(int) * len);
            for (int i = 1; 1 << i <= len; i++) {
                for (int j = 0; j + (1 << i) <= len; j++) {
                    mnhgt[i][j] = min(mnhgt[i - 1][j], mnhgt[i - 1][j + (1 << (i - 1))]);
                }
            }
        }

        int lcp(int l, int r)
        {
            if (l > r) swap(l, r);
            int idx = log2(++r - ++l);
            return min(mnhgt[idx][l], mnhgt[idx][r - (1 << idx)]);
        }
} sa;

char str[100010];
bool vis[100010 << 1];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        sa.reset();
        scanf("%s", str);
        char *s = str;
        while (*s) sa.str[sa.len++] = *s++;
        sa.str[sa.len++] = 1;
        s--;
        while (s >= str) sa.str[sa.len++] = *s--;

        sa.build();
        sa.calc_hgt();
        sa.calc_lcp();

        int sum = 0;
        int last = strlen(str);
        for (int d = 0; d < 2; d++) {
            memset(vis, 0, sizeof vis);
            for (int i = 1, len = sa.len; i < sa.len; i++) {
                len = min(len, sa.hgt[i]);

                if (sa.suff[i] < last) {
                    int cnt = sa.lcp(i, sa.rank[sa.len - sa.suff[i] - d]);
                    if (cnt > len) {
                        sum += cnt - len;
                        len = cnt;
                    }
                }
            }
        }

        printf("Case #%d: %d\n", task, sum);
    }

    return 0;
}

