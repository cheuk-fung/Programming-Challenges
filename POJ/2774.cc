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

class SuffixArray {
    // use Doubling Algorithm

    private:
        const static int MAX_LEN = 200012;
        const static int MAX_CHAR = 128;

        struct Suffix {
            int id;
            int key[2];
        };

        Suffix suffBuf[MAX_LEN];
        int intBuf[MAX_LEN];

        void cSort(Suffix* dest, Suffix* src, int key, int range)
        {
            int* cnt = intBuf;
            memset(cnt, 0, sizeof(int) * range);
            for (int i = 0; i < len; i++) cnt[src[i].key[key]]++;
            for (int i = 1; i < range; i++) cnt[i] += cnt[i - 1];
            for (int i = len - 1; i >= 0; i--) dest[--cnt[src[i].key[key]]] = src[i];
        }

    public:
        char str[MAX_LEN];
        int len;

        Suffix suff[MAX_LEN]; // suff[i]: the i-th *sorted* suffix
        int* rank;            // rank[i]: the rank of the i-th *original* suffix
        // suff[i] = j <=> rank[j] = i
 
        // LCP(i, j): the Longest Common Prefix of the i-th and j-th *sorted* suffixes
        int hgt[MAX_LEN];  //  hgt[i]: LCP(i - 1, i)

        void build()
        {
//            len = strlen(str);
            rank = intBuf;

            for (int i = 0; i < len; i++) {
                suffBuf[i].id = i;
                suffBuf[i].key[0] = str[i];
                suffBuf[i].key[1] = 0;
            }
            cSort(suff, suffBuf, 0, MAX_CHAR);

            for (int k = 1, maxRank; maxRank != len; k <<= 1) {
                rank[suff[0].id] = maxRank = 1;
                for (int i = 1; i < len; i++) {
                    if (suff[i - 1].key[0] < suff[i].key[0] || suff[i - 1].key[1] < suff[i].key[1])
                        rank[suff[i].id] = ++maxRank;
                    else rank[suff[i].id] = maxRank;
                }

                for (int i = 0; i < len; i++) {
                    suff[i].id = i;
                    suff[i].key[0] = rank[i];
                    suff[i].key[1] = i + k < len ? rank[i + k] : 0;
                }

                cSort(suffBuf, suff, 1, maxRank + 1);
                cSort(suff, suffBuf, 0, maxRank + 1);
            }

            for (int i = 0, j = 0; i < len; i++, j++)
                rank[suff[i].id] = j;
        }

        void getHgt()
        {
            for (int i = 0, k = 0; i < len; i++) {
                int j = rank[i] ? suff[rank[i] - 1].id : 0;
                if (k) k--;
                while (str[i + k] != '\0' && str[j + k] != '\0' && str[i + k] == str[j + k]) k++;
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
        if (sa.hgt[i] > ans && ((sa.suff[i - 1].id < mid && sa.suff[i].id > mid) || (sa.suff[i - 1].id > mid && sa.suff[i].id < mid)))
            ans = sa.hgt[i];

    printf("%d\n", ans);

    return 0;
}
