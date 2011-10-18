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

class SuffixArray {
    // use Doubling Algorithm

    private:
        const static int MAX_LEN = 200012;
        const static int MAX_CHAR = 128;

        int* n_rank;
        int int_buf_1[MAX_LEN], int_buf_2[MAX_LEN]; // used for ranking

        int cnt[MAX_LEN]; // used for counting sort

        void c_sort(int k, int range)
        {
            int* t_rank = n_rank;
            int tR = 0;
            for (int i = len - k; i < len; i++) t_rank[tR++] = i;
            for (int i = 0; i < len; i++)
                if (suff[i] >= k) t_rank[tR++] = suff[i] - k;

            for (int i = 0; i < len; i++) cnt[rank[i]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1, j; i >= 0; i--) {
                j = t_rank[i];
                suff[--cnt[rank[j]]] = j;
            }

            memset(cnt, 0, sizeof(int) * range);
        }

    public:
        char str[MAX_LEN];
        int len;

        int suff[MAX_LEN]; // suff[i]: the i-th *sorted* suffix
        int* rank;         // rank[i]: the rank of the i-th *original* suffix
        // suff[i] = j <=> rank[j] = i

        // LCP(i, j): the Longest Common Prefix of the i-th and j-th *sorted* suffixes
        int hgt[MAX_LEN];  //  hgt[i]: LCP(i - 1, i)

        void reset() {
            memset(int_buf_1, 0, sizeof(int_buf_1));
            memset(int_buf_2, 0, sizeof(int_buf_2));
            memset(cnt, 0, sizeof(cnt));
            memset(suff, 0, sizeof(suff));
            memset(hgt, 0, sizeof(hgt));
        }

        void build()
        {
            len = strlen(str);
            rank = int_buf_1;
            n_rank = int_buf_2;

            for (int i = 0; i < len; i++) {
                rank[i] = str[i];
                suff[i] = i;
            }
            c_sort(0, MAX_CHAR);

            for (int k = 1, max_rank = MAX_CHAR; max_rank != len; k <<= 1) {
                c_sort(k, max_rank + 1);

                max_rank = n_rank[suff[0]] = 1;
                for (int i = 1; i < len; i++) {
                    if (rank[suff[i - 1]] == rank[suff[i]] && rank[suff[i - 1] + k] == rank[suff[i] + k])
                        n_rank[suff[i]] = max_rank;
                    else n_rank[suff[i]] = ++max_rank;
                }

                int* tp = rank;
                rank = n_rank;
                n_rank = tp;
            }
            for (int i = 0; i < len; i++) rank[i]--;
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = suff[rank[i] - 1]; str[i + k] == str[j + k]; k++) ;
        }
};

SuffixArray sa;

char s[100010];

int main()
{
    scanf("%s", s);
    for (int i = 0; s[i] != '\0'; i++) sa.str[sa.len++] = s[i];
    int mid = sa.len;
    sa.str[sa.len++] = 1;
    scanf("%s", s);
    for (int i = 0; s[i] != '\0'; i++) sa.str[sa.len++] = s[i];
    sa.str[sa.len] = '\0';

    sa.build();
    sa.calc_hgt();

    int ans = 0;
    for (int i = 1; i < sa.len; i++)
        if (sa.hgt[i] > ans && ((sa.suff[i - 1] < mid && sa.suff[i] > mid) || (sa.suff[i - 1] > mid && sa.suff[i] < mid)))
            ans = sa.hgt[i];

    printf("%d\n", ans);

    return 0;
}
