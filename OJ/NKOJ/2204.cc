/*
 *  SRC: NKOJ 2204
 * PROB: Threatening Letter
 * ALGO: Suffix Array
 * DATE: Oct 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

class Suffix_Array {
    private:
        enum {
            MAXLEN = 100010,
            MAXCHAR = 128,
        };

        int *nrank;
        int rbuf[2][MAXLEN];
        int cnt[MAXLEN];

        void csort(int k, int range)
        {
            int t = 0;
            for (int i = len - k; i < len; i++) nrank[t++] = i;
            for (int i = 0; i < len; i++) {
                if (suff[i] >= k) nrank[t++] = suff[i] - k;
            }

            for (int i = 0; i < len; i++) cnt[rank[i]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1, j; i >= 0; i--) {
                j = nrank[i];
                suff[--cnt[rank[j]]] = j;
            }

            memset(cnt, 0, sizeof(int) * range);
        }

    public:
        enum { DELIM = 10 };
        char str[MAXLEN];
        int len;

        int suff[MAXLEN];
        int *rank;

        int hgt[MAXLEN];

        void reset()
        {
            memset(rbuf, 0, sizeof rbuf);
            memset(cnt, 0, sizeof cnt);
            memset(suff, 0, sizeof suff);
            memset(hgt, 0, sizeof hgt);
        }

        void build()
        {
            len = strlen(str);
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
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = rank[i] ? suff[rank[i] - 1] : len; str[i + k] == str[j + k]; k++)
                    ;
        }
} sa;

int len[50010];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        char c;
        while (isspace(c = getchar())) ;
        sa.str[i] = c;
    }
    sa.str[n] = sa.DELIM;
    for (int i = 0; i < m; i++) {
        char c;
        while (isspace(c = getchar())) ;
        sa.str[i + n + 1] = c;
    }
    sa.str[n + m + 1] = '\0';

    sa.build();
    sa.calc_hgt();

    for (int prev = 0, next = 0; prev < sa.len; prev = next) {
        next = prev + 1;
        while (next < sa.len && sa.suff[next] > n) next++;
        for (int i = prev + 1, now = sa.len; i < next; i++) {
            now = min(now, sa.hgt[i]);
            assert(sa.suff[i] >= n + 1);
            len[sa.suff[i] - n - 1] = now;
        }
        if (next != sa.len) {
            for (int i = next - 1, now = sa.len; i > prev; i--) {
                now = min(now, sa.hgt[i + 1]);
                assert(sa.suff[i] >= n + 1);
                len[sa.suff[i] - n - 1] = max(len[sa.suff[i] - n - 1], now);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < m; ) {
        cnt++;
        i += len[i];
    }

    printf("%d\n", cnt);

    return 0;
}

