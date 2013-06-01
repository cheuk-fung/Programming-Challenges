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
#include <cmath>
#include <utility>
#include <algorithm>

using std::pair;
using std::make_pair;
using std::max;
using std::min;
using std::swap;

class Suffix_Array {
    // use Doubling Algorithm

    public:
        const static int MAXLEN = 40010;
        const static int MAXCHAR = 128;

        int n;			// length of s
        char s[MAXLEN];

        int suff[MAXLEN];	// suff[i]: the i-th *sorted* suffix
        int *rank, *nrank;	// rank[i]: the rank of the i-th *original* suffix
        // suff[i] = j <=> rank[j] = i

        // LCP(i, j): the Longest Common Prefix of the i-th and j-th *sorted* suffixes
        int hgt[MAXLEN];	// hgt[i]: LCP(i - 1, i)

        int rbuf[2][MAXLEN]; // used for ranking
        int cnt[MAXLEN]; // used for counting sort

        int maxsuff[20][MAXLEN], minhgt[20][MAXLEN];

        void csort(int k, int m)
        {
            memset(cnt, 0, sizeof(int) * m);

            int t = 0;
            for (int i = n - k; i < n; i++) nrank[t++] = i;
            for (int i = 0; i < n; i++)
                if (suff[i] >= k) nrank[t++] = suff[i] - k;

            for (int i = 0; i < n; i++) cnt[rank[i]]++;
            for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) {
                t = nrank[i];
                suff[--cnt[rank[t]]] = t;
            }
        }

        void build()
        {
            n = strlen(s);
            rank = rbuf[0];
            nrank = rbuf[1];

            for (int i = 0; i < n; i++) {
                rank[i] = s[i];
                suff[i] = i;
            }
            int m = MAXCHAR;
            csort(0, m);

            for (int k = 1, r = 1; r < n; k <<= 1, m = r + 1) {
                csort(k, m);

                r = nrank[suff[0]] = 1;
                for (int i = 1; i < n; i++) {
                    if (rank[suff[i - 1]] == rank[suff[i]] && rank[suff[i - 1] + k] == rank[suff[i] + k]) {
                        nrank[suff[i]] = r;
                    } else {
                        nrank[suff[i]] = ++r;
                    }
                }

                swap(rank, nrank);
            }
            for (int i = 0; i < n; i++) rank[i]--;
        }

        void calc_hgt()
        {
            for (int i = 0, k = 0; i < n; i++) {
                if (!rank[i]) continue;

                int t = suff[rank[i] - 1];
                while (s[i + k] == s[t + k]) k++;
                hgt[rank[i]] = k;
                if (k) k--;
            }
        }

        void calc_lcp()
        {
            memcpy(maxsuff[0], suff, sizeof(int) * n);
            memcpy(minhgt[0], hgt, sizeof(int) * n);
            for (int i = 1; 1 << i <= n; i++)
                for (int j = 0; j + (1 << i) <= n; j++) {
                    maxsuff[i][j] = max(maxsuff[i - 1][j], maxsuff[i - 1][j + (1 << (i - 1))]);
                    minhgt[i][j] = min(minhgt[i - 1][j], minhgt[i - 1][j + (1 << (i - 1))]);
                }

        }

        pair<int, int> lcp(int l, int r) // lcp of *sorted* suffixes between [l, r)
        {
            int idx = log2(r - l);
            int pos = max(maxsuff[idx][l], maxsuff[idx][r - (1 << idx)]);

            int length;
            if (l + 1 == r) {
                length = n - suff[l];
            } else {
                idx = log2(r - ++l);
                length = min(minhgt[idx][l], minhgt[idx][r - (1 << idx)]);
            }

            return make_pair(length, pos);
        }
};

Suffix_Array sa;

int main()
{
    int m;
    while (scanf("%d", &m), m) {
        memset(&sa, 0, sizeof(Suffix_Array));

        scanf("%s", sa.s);

        sa.build();
        sa.calc_hgt();
        sa.calc_lcp();

        int longest = 0, pos;
        for (int i = 0; i + m <= sa.n; i++) {
            pair<int, int> p = sa.lcp(i, i + m);
            if (p.first > longest) {
                longest = p.first;
                pos = p.second;
            } else if (p.first == longest && p.second > pos) {
                pos = p.second;
            }
        }

        if (longest) printf("%d %d\n", longest, pos);
        else puts("none");
    }

    return 0;
}

