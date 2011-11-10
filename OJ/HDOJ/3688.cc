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

using std::max;

const int MAX_N = 110,
          MAX_M = 10010;

int n, m;
short map[MAX_N][MAX_M],
      row[MAX_N][MAX_M],
      col[MAX_M][MAX_N],
      row_cnt[MAX_N],
      col_cnt[MAX_M];

int check(int h)
{
    int res = 0;
    for (int i = 0; i < n; i++) {
        int k, prev_pos, last_pos;
        bool can_light = false;
        for (k = 0; k < row_cnt[i]; k++) {
            int j = row[i][k];
            if (map[i][j] < h) continue;
            if (j + 1 > h) return 0;
            res = max(res, j + 1);
            last_pos = prev_pos = j;
            can_light = true;
            break;
        }
        if (!can_light) return 0;
        for (k++; k < row_cnt[i]; k++) {
            int j = row[i][k];
            if (map[i][j] < h) continue;
            if ((j - prev_pos + 2) / 2 > h) return 0;
            res = max(res, (j - prev_pos + 2) / 2);
            last_pos = prev_pos = j;
        }
        if (m - last_pos > h) return 0;
        res = max(res, m - last_pos);
    }

    for (int j = 0; j < m; j++) {
        int k, prev_pos, last_pos;
        bool can_light = false;
        for (k = 0; k < col_cnt[j]; k++) {
            int i = col[j][k];
            if (map[i][j] < h) continue;
            if (i + 1 > h) return 0;
            res = max(res, i + 1);
            last_pos = prev_pos = i;
            can_light = true;
            break;
        }
        if (!can_light) return 0;
        for (k++; k < col_cnt[j]; k++) {
            int i = col[j][k];
            if (map[i][j] < h) continue;
            if ((i - prev_pos + 2) / 2 > h) return 0;
            res = max(res, (i - prev_pos + 2) / 2);
            last_pos = prev_pos = i;
        }
        if (n - last_pos > h) return 0;
        res = max(res, n - last_pos);
    }

    return res;
}

int main()
{
    while (scanf("%d%d", &n, &m), n && m) {
        memset(map, 0, sizeof(map));
        memset(row_cnt, 0, sizeof(row_cnt));
        memset(col_cnt, 0, sizeof(col_cnt));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                scanf("%hd", &map[i][j]);
                if (map[i][j]) {
                    row[i][row_cnt[i]++] = j;
                    col[j][col_cnt[j]++] = i;
                }
            }

        bool cont = false;
        for (int i = 0; i < n; i++)
            if (!row_cnt[i]) {
                puts("NO ANSWER!");
                cont = true;
                break;
            }
        if (cont) continue;
        for (int j = 0; j < m; j++)
            if (!col_cnt[j]) {
                puts("NO ANSWER!");
                cont = true;
                break;
            }
        if (cont) continue;

        int ans = 0;
        for (int h = m + n; h > 0; h--) {
            int tmp = check(h);
            if (tmp) {
                ans = tmp;
                h = tmp;
            }
            else if (ans) break;
        }

        if (!ans) puts("NO ANSWER!");
        else printf("%d\n", ans);
    }

    return 0;
}
