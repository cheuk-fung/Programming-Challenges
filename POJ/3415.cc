/*
 *  SRC: POJ 3415
 * PROB: Common Substrings
 * ALGO: Suffix Array
 * DATE: Oct 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

enum {
    MAXN = 100010 << 1
};

class Suffix_Array {
    private:
        enum {
            MAXLEN = MAXN,
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

struct Node {
    int pos;
    long long sum;
} S[MAXN];
long long cnt[MAXN];

template<typename Comparator>
long long work(int k, int delim, Comparator comp)
{
    long long res = 0;
    for (int i = 0; i < sa.len; i++) {
        cnt[i + 1] = cnt[i] + comp(sa.suff[i], delim);
    }
    for (int i = 1, top = 1; i < sa.len; i++) {
        while (top > 1 && sa.hgt[i] <= sa.hgt[S[top - 1].pos]) top--;
        S[top].pos = i;
        S[top].sum = sa.hgt[i] >= k ? S[top - 1].sum + (sa.hgt[i] - k + 1) * (cnt[i] - cnt[S[top - 1].pos]) : 0;
        if (comp(delim, sa.suff[i])) res += S[top].sum;
        top++;
    }
    return res;
}

int main()
{
    int k;
    while (scanf("%d", &k), k) {
        sa.reset();
        scanf("%s", str);
        char *s = str;
        while (*s) sa.str[sa.len++] = *s++;
        int delim = sa.len;
        sa.str[sa.len++] = 1;
        scanf("%s", str);
        s = str;
        while (*s) sa.str[sa.len++] = *s++;
        sa.build();

        long long ans = work(k, delim, less<int>()) + work(k, delim, greater<int>());
        printf("%lld\n", ans);
    }

    return 0;
}

