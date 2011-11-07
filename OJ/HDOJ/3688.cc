/*
 *  SRC: HDOJ 3688
 * PROB: Searchlights
 * ALGO: Bisection
 * DATE: Nov 07, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

int cover_cnt;

class SegTree {
    private:
        struct Tnode {
            short a, b;
            short len;
            int cover;
            bool full;
        };
        Tnode node[100000];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx].a = a;
            node[idx].b = b;

            if (a + 1 < b) {
                build(a, (a + b) / 2, idx * 2);
                build((a + b) / 2, b, idx * 2 + 1);
            }
        }

        void insert(int c, int d, int v, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                node[idx].cover = v;
                node[idx].full = true;
                node[idx].len = node[idx].b - node[idx].a;
                return ;
            }

            if (node[idx].cover != v) {
                node[idx].cover = v;
                node[idx].full = false;
                node[idx * 2].full = false;
                node[idx * 2].len = 0;
                node[idx * 2 + 1].full = false;
                node[idx * 2 + 1].len = 0;
            }

            if (node[idx].full) return ;

            if (c < (node[idx].a + node[idx].b) / 2)
                insert(c, d, v, idx * 2);
            if (d > (node[idx].a + node[idx].b) / 2)
                insert(c, d, v, idx * 2 + 1);
            node[idx].len = node[idx * 2].len + node[idx * 2 + 1].len;
        }

        short query()
        {
            return node[1].len;
        }
};
SegTree st;

const int MAX_N = 110,
          MAX_M = 10010;

int n, m;
short map[MAX_N][MAX_M],
      row[MAX_N][MAX_M],
      col[MAX_M][MAX_N],
      row_cnt[MAX_N],
      col_cnt[MAX_M];

struct Searchlight {
    short x, y, h;

    Searchlight(short _x = 0, short _y = 0, short _h = 0)
        : x(_x), y(_y), h(_h)
    { }

    bool operator <(const Searchlight &other) const { return h < other.h; }
};
Searchlight sl[MAX_N * MAX_M];
int sl_cnt;

bool check(int h)
{
    for (int i = 0; i < n; i++) {
        bool not_insert = true;
        for (int k = 0; k < row_cnt[i]; k++) {
            int j = row[i][k];
            if (map[i][j] < h) continue;
            not_insert = false;

            int l = j - h + 1 < 0 ? 0 : j - h + 1,
                r = j + h < m ? j + h : m;
            st.insert(l, r, cover_cnt);
            if (st.query() == m) break;
        }
        cover_cnt++;

        if (not_insert) return false;
        if (st.query() != m) return false;
    }

    for (int j = 0; j < m; j++) {
        bool not_insert = true;
        for (int k = 0; k < col_cnt[j]; k++) {
            int i = col[j][k];
            if (map[i][j] < h) continue;
            not_insert = false;

            int l = i - h + 1 < 0 ? 0 : i - h + 1,
                r = i + h < n ? i + h : n;
            st.insert(l, r, cover_cnt);
            if (st.query() == n) break;
        }
        cover_cnt++;

        if (not_insert) return false;
        if (st.query() != n) return false;
    }

    return true;
}

int main()
{
    st.build(0, MAX_M);

    while (scanf("%d%d", &n, &m), n && m) {
        memset(map, 0, sizeof(map));
        memset(row_cnt, 0, sizeof(row_cnt));
        memset(col_cnt, 0, sizeof(col_cnt));
        sl_cnt = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                scanf("%hd", &map[i][j]);
                if (map[i][j]) {
                    sl[sl_cnt++] = Searchlight(i, j, map[i][j]);
                    row[i][row_cnt[i]++] = j;
                    col[j][col_cnt[j]++] = i;
                }
            }
        sort(sl, sl + sl_cnt);

        int l = 0, r = 0;
        if (check(sl[0].h)) r = sl[0].h;
        else {
            for (int i = 1; i < sl_cnt; i++) {
                if (check(sl[i].h)) {
                    l = sl[i - 1].h;
                    r = sl[i].h;
                    break;
                }
                else
                    while (i + 1 < sl_cnt && sl[i + 1].h == sl[i].h) i++;
            }
        }

        if (!r) {
            puts("NO ANSWER!");
            continue;
        }

        while (l < r) {
            int mid = (l + r - 1) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }

    return 0;
}
