/*
 *  SRC: POJ 3882
 * PROB: Stammering Aliens
 * ALGO: Suffix Array
 * DATE: Aug 21, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <cmath>

using std::pair;
using std::make_pair;
using std::max;
using std::min;
using std::swap;

class Suffix_Array {
    // use Doubling Algorithm

    private:
        const static int MAXLEN = 40010;
        const static int MAXCHAR = 128;

        int *nrank;
        int rbuf[2][MAXLEN]; // used for ranking

        int cnt[MAXLEN]; // used for counting sort

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

        int suff[MAXLEN]; // suff[i]: the i-th *sorted* suffix
        int *rank;         // rank[i]: the rank of the i-th *original* suffix
        // suff[i] = j <=> rank[j] = i

        // LCP(i, j): the Longest Common Prefix of the i-th and j-th *sorted* suffixes
        int hgt[MAXLEN];  //  hgt[i]: LCP(i - 1, i)

        int maxsuff[20][MAXLEN], minhgt[20][MAXLEN];

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

        void calc_lcp()
        {
            memcpy(maxsuff[0], suff, sizeof(int) * len);
            memcpy(minhgt[0], hgt, sizeof(int) * len);
            for (int i = 1; 1 << i <= len; i++)
                for (int j = 0; j + (1 << i) <= len; j++) {
                    maxsuff[i][j] = max(maxsuff[i - 1][j], maxsuff[i - 1][j + (1 << (i - 1))]);
                    minhgt[i][j] = min(minhgt[i - 1][j], minhgt[i - 1][j + (1 << (i - 1))]);
                }

        }

        pair<int, int> lcp(int l, int r) // [l, r)
        {
            int idx = log2(r - l);
            int pos = max(maxsuff[idx][l], maxsuff[idx][r - (1 << idx)]);

            l++;
            idx = log2(r - l);
            int res = min(minhgt[idx][l], minhgt[idx][r - (1 << idx)]);

            return make_pair(res, pos);
        }
};

Suffix_Array sa;

int main()
{
    int m;
    while (scanf("%d", &m), m) {
        scanf("%s", sa.str);
        if (m == 1) {
            printf("%d %d\n", strlen(sa.str), 0);
            continue;
        }

        sa.build();
        sa.calc_hgt();
        sa.calc_lcp();

        int longest = 0, pos;
        for (int i = 0; i + m <= sa.len; i++) {
            pair<int, int> p = sa.lcp(i, i + m);
            if (p.first > longest) {
                longest = p.first;
                pos = p.second;
            }
            else if (p.first == longest && p.second > pos) pos = p.second;
        }

        if (longest) printf("%d %d\n", longest, pos);
        else puts("none");

        sa.reset();
    }

    return 0;
}


