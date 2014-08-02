/*
 *  SRC: POJ
 * PROB: Long Long Message
 * ALGO: Suffix Array
 * DATE: Jul 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

class SuffixArray
{
    // use Doubling Algorithm

    private:
        const static int MAX_LEN = 200012;
        const static int MAX_CHAR = 128;

        int* nRank;
        int intBuf1[MAX_LEN], intBuf2[MAX_LEN]; // used for ranking

        int cnt[MAX_LEN]; // used for counting sort

        void cSort(int k, int range)
        {
            int* tRank = nRank;
            int tR = 0;
            for (int i = len - k; i < len; i++) tRank[tR++] = i;
            for (int i = 0; i < len; i++)
                if (suff[i] >= k) tRank[tR++] = suff[i] - k;

            for (int i = 0; i < len; i++) cnt[rank[i]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1, j; i >= 0; i--) {
                j = tRank[i];
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

        void build()
        {
            //            len = strlen(str);
            rank = intBuf1;
            nRank = intBuf2;

            for (int i = 0; i < len; i++) {
                rank[i] = str[i];
                suff[i] = i;
            }
            cSort(0, MAX_CHAR);

            for (int k = 1, maxRank = MAX_CHAR; maxRank != len; k <<= 1) {
                cSort(k, maxRank + 1);

                maxRank = nRank[suff[0]] = 1;
                for (int i = 1; i < len; i++) {
                    if (rank[suff[i - 1]] == rank[suff[i]] && rank[suff[i - 1] + k] == rank[suff[i] + k])
                        nRank[suff[i]] = maxRank;
                    else nRank[suff[i]] = ++maxRank;
                }

                int* tp = rank;
                rank = nRank;
                nRank = tp;
            }
            for (int i = 0; i < len; i++) rank[i]--;
        }

        void getHgt()
        {
            for (int i = 0, k = 0; i < len; i++) {
                int j = rank[i] ? suff[rank[i] - 1] : 0;
                if (k) k--;
                while (str[i + k] && str[j + k] && str[i + k] == str[j + k]) k++;
                hgt[rank[i]] = k;
            }
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
    sa.getHgt();

    int ans = 0;
    for (int i = 1; i < sa.len; i++)
        if (sa.hgt[i] > ans && ((sa.suff[i - 1] < mid && sa.suff[i] > mid) || (sa.suff[i - 1] > mid && sa.suff[i] < mid)))
            ans = sa.hgt[i];

    printf("%d\n", ans);

    return 0;
}
