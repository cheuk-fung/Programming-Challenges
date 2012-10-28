/*
 *  SRC: POJ 3294
 * PROB: Life Forms
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
            MAXLEN = 100110,
            MAXCHAR = 256
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
        }

        void calc_hgt()
        {
            for (int i = 0, j, k = 0; i < len; hgt[rank[i++]] = k)
                for (k ? k-- : 0, j = rank[i] ? suff[rank[i] - 1] : len; str[i + k] == str[j + k]; k++)
                    ;
        }
} sa;

int n;
char dna[1010];
int first_pos[110];
int vis[110];

bool check(int x, bool is_print = false)
{
    for (int left = 1, right = 1; left < sa.len; ) {
        while (left < sa.len && sa.hgt[left] < x) left++;
        if (left == sa.len) return false;
        right = left + 1;
        while (right < sa.len && sa.hgt[right] >= x) right++;
        memset(vis, 0, sizeof vis);
        for (int i = left - 1; i < right; i++) {
            vis[upper_bound(first_pos, first_pos + n, sa.suff[i]) - first_pos - 1] = 1;
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) cnt += vis[i];
        if (cnt > n / 2) {
            if (!is_print) return true;
            for (int i = sa.suff[left - 1]; i < sa.suff[left - 1] + x; i++) putchar(sa.str[i]);
            putchar(10);
        }

        left = right + 1;
    }

    return false;
}

int main()
{
    bool first_case = true;
    while (scanf("%d", &n), n) {
        if (!first_case) putchar(10);
        first_case = false;

        sa.reset();

        int delim = 'z' + 1;
        size_t mlen = 1010;
        for (int i = 0; i < n; i++) {
            scanf("%s", dna);
            mlen = min(mlen, strlen(dna));
            first_pos[i] = sa.len;
            char *s = dna;
            while (*s) sa.str[sa.len++] = *s++;
            sa.str[sa.len++] = delim++;
        }
        if (n == 1) {
            puts(dna);
            continue;
        }
        sa.build();
        sa.calc_hgt();

        int low = 0, high = mlen;
        while (low < high) {
            int mid = (low + high + 1) >> 1;
            if (check(mid)) low = mid;
            else high = mid - 1;
        }

        if (!low) puts("?");
        else check(low, true);
    }

    return 0;
}

