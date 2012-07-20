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
        const static int MAX_LEN = 40010;
        const static int MAX_CHAR = 128;

        int *n_rank;
        int intbuf1[MAX_LEN], intbuf2[MAX_LEN]; // used for ranking

        int cnt[MAX_LEN]; // used for counting sort

        void c_sort(int k, int range)
        {
            int t = 0;
            for (int i = len - k; i < len; i++) n_rank[t++] = i;
            for (int i = 0; i < len; i++)
                if (suff[i] >= k) n_rank[t++] = suff[i] - k;

            for (int i = 0; i < len; i++) cnt[rank[i]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1, j; i >= 0; i--) {
                j = n_rank[i];
                suff[--cnt[rank[j]]] = j;
            }

            memset(cnt, 0, sizeof(int) * range);
        }

    public:
        char str[MAX_LEN];
        int len;

        int suff[MAX_LEN]; // suff[i]: the i-th *sorted* suffix
        int *rank;         // rank[i]: the rank of the i-th *original* suffix
        // suff[i] = j <=> rank[j] = i

        // LCP(i, j): the Longest Common Prefix of the i-th and j-th *sorted* suffixes
        int hgt[MAX_LEN];  //  hgt[i]: LCP(i - 1, i)

        int max_suff[20][MAX_LEN], min_hgt[20][MAX_LEN];

        void reset()
        {
            memset(intbuf1, 0, sizeof intbuf1);
            memset(intbuf2, 0, sizeof intbuf2);
            memset(cnt, 0, sizeof cnt);
            memset(suff, 0, sizeof suff);
            memset(hgt, 0, sizeof hgt);
        }

        void build()
        {
            len = strlen(str);
            rank = intbuf1;
            n_rank = intbuf2;

            for (int i = 0; i < len; i++) {
                rank[i] = str[i];
                suff[i] = i;
            }
            c_sort(0, MAX_CHAR);

            for (int k = 1, max_rank = MAX_CHAR; max_rank != len; k <<= 1) {
                c_sort(k, max_rank + 1);

                max_rank = n_rank[suff[0]] = 1;
                for (int i = 1; i < len; i++) {
                    if (rank[suff[i - 1]] == rank[suff[i]] && rank[suff[i - 1] + k] == rank[suff[i] + k]) {
                        n_rank[suff[i]] = max_rank;
                    } else {
                        n_rank[suff[i]] = ++max_rank;
                    }
                }

                swap(rank, n_rank);
            }
            for (int i = 0; i < len; i++) rank[i]--;
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = suff[rank[i] - 1]; str[i + k] == str[j + k]; k++)
                    ;
        }

        void calc_lcp()
        {
            memcpy(max_suff[0], suff, sizeof(int) * len);
            memcpy(min_hgt[0], hgt, sizeof(int) * len);
            for (int i = 1; 1 << i <= len; i++)
                for (int j = 0; j + (1 << i) <= len; j++) {
                    max_suff[i][j] = max(max_suff[i - 1][j], max_suff[i - 1][j + (1 << (i - 1))]);
                    min_hgt[i][j] = min(min_hgt[i - 1][j], min_hgt[i - 1][j + (1 << (i - 1))]);
                }

        }

        pair<int, int> lcp(int l, int r) // [l, r)
        {
            int idx = log2(r - l);
            int pos = max(max_suff[idx][l], max_suff[idx][r - (1 << idx)]);

            l++;
            idx = log2(r - l);
            int res = min(min_hgt[idx][l], min_hgt[idx][r - (1 << idx)]);

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


