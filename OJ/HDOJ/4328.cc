/*
 *  SRC: HDOJ 4328
 * PROB: Cut the cake
 * ALGO: DP
 * DATE: Jul 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Point {
    int u, l, r;

    int perimeter() const
    {
        return (u + (r + l - 1)) << 1;
    }
} p_buf[2][1010];
Point *prev = p_buf[0];
Point *curr = p_buf[1];

int r, c;
char mat[1010][1010];

int run(char ch)
{
    memset(p_buf, 0, sizeof p_buf);

    int res = 0;
    for (int i = 0; i < r; i++) {
        memset(curr, 0, sizeof p_buf[0]);
        for (int j = 0; j < c; j++) {
            if (mat[i][j] == ch) curr[j].u = prev[j].u + 1;
        }

        for (int j = 0, l_cnt = 0; j < c; j++) {
            if (mat[i][j] == ch) {
                if (prev[j].l) curr[j].l = min(prev[j].l, ++l_cnt);
                else curr[j].l = ++l_cnt;
            } else {
                l_cnt = 0;
            }
        }

        for (int j = c - 1, r_cnt = 0; j >= 0; j--) {
            if (mat[i][j] == ch) {
                if (prev[j].r) curr[j].r = min(prev[j].r, ++r_cnt);
                else curr[j].r = ++r_cnt;
            } else {
                r_cnt = 0;
            }
        }

        for (int j = 0; j < c; j++) {
            res = max(res, curr[j].perimeter());
        }

        swap(curr, prev);
    }

    return res;
}

int RB()
{
    memset(p_buf, 0, sizeof p_buf);

    int res = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i > 0 && mat[i][j] != mat[i - 1][j]) curr[j].u = prev[j].u + 1;
            else curr[j].u = 1;
        }

        curr[0].l = 1;
        for (int j = 1; j < c; j++) {
            if (mat[i][j] != mat[i][j - 1]) curr[j].l = min(prev[j - 1].l, curr[j - 1].l) + 1;
            else curr[j].l = 1;
        }

        for (int j = 0; j < c; j++) {
            res = max(res, min(curr[j].u, curr[j].l) * 4);
        }

        swap(curr, prev);
    }

    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {

        scanf("%d%d", &r, &c);
        for (int i = 0; i < r; i++) {
            scanf("%s", mat[i]);
        }

        int ans = max(max(run('R'), run('B')), RB());

        printf("Case #%d: %d\n", task, ans);
    }

    return 0;
}
