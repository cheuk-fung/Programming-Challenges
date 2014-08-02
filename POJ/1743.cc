/*
 *  SRC: POJ 1743
 * PROB: Musical Theme
 * ALGO: Suffix Array
 * DATE: Oct 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

class Suffix_Array {
    private:
        enum {
            MAXLEN = 20012,
            MAXCHAR = 180
        };

        int *nrank;
        int rbuf[2][MAXLEN];
        int cnt[MAXLEN];

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
        int str[MAXLEN];
        int len;

        int suff[MAXLEN], hgt[MAXLEN];
        int *rank;

        void reset()
        {
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
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = rank[i] ? suff[rank[i] - 1] : len; str[i + k] == str[j + k]; k++)
                    ;
        }
} sa;

bool check(int x)
{
    for (int left = 1, right = 1; left < sa.len; ) {
        while (left < sa.len && sa.hgt[left] < x) left++;
        if (left == sa.len) return false;

        right = left;
        while (right < sa.len && sa.hgt[right] >= x) right++;
        if (*min_element(sa.suff + left - 1, sa.suff + right) + x <= *max_element(sa.suff + left - 1, sa.suff + right)) return true;

        left = right;
    }

    return false;
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        if (n == 1) {
            scanf("%*d");
            puts("0");
            continue;
        }

        sa.reset();
        for (int i = 0; i < n; i++) scanf("%d", &sa.str[i]);
        for (int i = n - 1; i > 0; i--) sa.str[i] -= sa.str[i - 1];
        for (int i = 0; i < n - 1; i++) sa.str[i] = sa.str[i + 1] + 90;
        sa.len = n - 1;
        sa.build();
        sa.calc_hgt();

        int low = 0, high = n;
        while (low < high) {
            int mid = (low + high + 1) >> 1;
            if (check(mid)) low = mid;
            else high = mid - 1;
        }
        printf("%d\n", low >= 4 ? low + 1 : 0);
    }

    return 0;
}

