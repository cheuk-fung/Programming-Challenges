/*
 *  SRC: POJ 3261
 * PROB: Milk Patterns
 * ALGO: Suffix Array
 * DATE: Oct 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

class Suffix_Array {
    private:
        enum {
            MAXLEN = 20048,
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
        int MAXCHAR;
        int len;
        int str[MAXLEN];
        int suff[MAXLEN], hgt[MAXLEN];
        int *rank;

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

map<int, int> milk;

bool check(int x, int k)
{
    for (int left = 1, right = 1; left < sa.len; ) {
        while (left < sa.len && sa.hgt[left] < x) left++;
        if (left == sa.len) return false;
        right = left + 1;
        while (right < sa.len && sa.hgt[right] >= x) right++;
        if (right - left + 1 >= k) return true;
        left = right + 1;
    }
    return false;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    int idx = 1;
    for (int i = 0; i < n; i++) {
        int day;
        scanf("%d", &day);
        if (!milk.count(day)) milk[day] = idx++;
        sa.str[i] = milk[day];
    }
    sa.len = n;
    sa.MAXCHAR = idx + 10;
    sa.build();
    sa.calc_hgt();

    int low = 0, high = n;
    while (low < high) {
        int mid = (low + high + 1) >> 1;
        if (check(mid, k)) low = mid;
        else high = mid - 1;
    }
    printf("%d\n", low);

    return 0;
}

