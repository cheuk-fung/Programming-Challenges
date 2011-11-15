/*
 *  SRC: POJ 3829
 * PROB: Seat taking up is tough
 * ALGO: NULL
 * DATE: Nov 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;
using std::pair;

const pair<int, int> FAIL(-1, -1);

struct Student {
    int h, m, q, id;
    pair<int, int> ans;

    bool operator <(const Student &other) const
    {
        if (h == other.h) return m < other.m;
        return h < other.h;
    }
};
Student stu[100];

bool cmp_id(const Student &a, const Student &b) { return a.id < b.id; }

struct Point {
    int x, y, f;

    bool operator <(const Point &other) const { return f > other.f; }
};
Point seat[1000];

int n, m, k, seat_cnt;
bool vis[100][100];

pair<int, int> find_row(int p)
{
    if (stu[p].q > m) return FAIL;

    for (int i = 0, j; i < seat_cnt; i++)
        if (!vis[seat[i].x][seat[i].y]) {
            if (seat[i].y + stu[p].q > m) continue;
            for (j = 1; j < stu[p].q; j++)
                if (vis[seat[i].x][seat[i].y + j]) break;
            if (j == stu[p].q) {
                for (int j = 0; j < stu[p].q; j++)
                    vis[seat[i].x][seat[i].y + j] = 1;
                return pair<int, int>(seat[i].x, seat[i].y);
            }
        }
    return FAIL;
}

pair<int, int> find_best()
{
    for (int i = 0; i < seat_cnt; i++)
        if (!vis[seat[i].x][seat[i].y]) {
            vis[seat[i].x][seat[i].y] = 1;
            return pair<int, int>(seat[i].x, seat[i].y);
        }
    return FAIL;
}

int main()
{
    while (scanf("%d%d%d", &n, &m, &k), n && m && k) {
        memset(vis, 0, sizeof(vis));

        seat_cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                int f;
                scanf("%d", &f);
                seat[seat_cnt++] = (Point){i, j, f};
            }
        sort(seat, seat + seat_cnt);

        for (int i = 0; i < k; i++) {
            scanf("%d:%d %d", &stu[i].h, &stu[i].m, &stu[i].q);
            stu[i].id = i;
        }
        sort(stu, stu + k);

        for (int i = 0; i < k; i++) {
            pair<int, int> ans = find_row(i);
            if (ans == FAIL) ans = find_best();
            stu[i].ans = ans;
        }
        sort(stu, stu + k, cmp_id);

        for (int i = 0; i < k; i++) {
            if (stu[i].ans == FAIL) puts("-1");
            else printf("%d %d\n", stu[i].ans.first + 1, stu[i].ans.second + 1);
        }
    }

    return 0;
}
