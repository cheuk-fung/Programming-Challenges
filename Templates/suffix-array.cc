/*
 *  SRC: POJ 2774
 * PROB: Long Long Message
 * ALGO: Suffix Array
 * DATE: Jul 22, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

class Suffix_Array {
    // use Doubling Algorithm

    public:
        const static int MAXLEN = 200012;
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
};

Suffix_Array sa;

char s[100010];

int main()
{
    scanf("%s", s);
    for (int i = 0; s[i] != '\0'; i++) sa.s[sa.n++] = s[i];
    int mid = sa.n;
    sa.s[sa.n++] = 1;
    scanf("%s", s);
    for (int i = 0; s[i] != '\0'; i++) sa.s[sa.n++] = s[i];
    sa.s[sa.n] = '\0';

    sa.build();
    sa.calc_hgt();

    int ans = 0;
    for (int i = 1; i < sa.n; i++)
        if (sa.hgt[i] > ans && ((sa.suff[i - 1] < mid && sa.suff[i] > mid) || (sa.suff[i - 1] > mid && sa.suff[i] < mid)))
            ans = sa.hgt[i];

    printf("%d\n", ans);

    return 0;
}
