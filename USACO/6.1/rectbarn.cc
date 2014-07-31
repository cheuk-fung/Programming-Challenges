/*
ID: os.idea1
LANG: C++
TASK: rectbarn
*/
#include <cstdio>

FILE *fin, *fout;

inline int fmin(short a, short b)
{
    if (!a) return b;
    return a < b ? a : b;
}

struct Point {
    short u, l, r;

    int area() const { return (int)u * (int)(r + l - 1); }
} p_buf[2][3010];
Point *prev = p_buf[0];
Point *curr = p_buf[1];

int r, c, p;
bool map[3010][3010];
int ans;

int main()
{
    fin  = fopen("rectbarn.in", "r");
    fout = fopen("rectbarn.out", "w");

    fscanf(fin, "%d%d%d", &r, &c, &p);
    for (int i = 0; i < p; i++) {
        int x, y;
        fscanf(fin, "%d%d", &x, &y);
        map[x][y] = 1;
    }

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (map[i][j]) curr[j].u = 0;
            else curr[j].u = prev[j].u + 1;
        }
        for (int j = 1, l_cnt = 0; j <= c; j++) {
            if (map[i][j]) l_cnt = curr[j].l = 0;
            else curr[j].l = fmin(prev[j].l, ++l_cnt);
        }
        for (int j = c, r_cnt = 0; j > 0; j--) {
            if (map[i][j]) r_cnt = curr[j].r = 0;
            else curr[j].r = fmin(prev[j].r, ++r_cnt);
        }
        for (int j = 1; j <= c; j++)
            if (curr[j].area() > ans) ans = curr[j].area();

        Point *temp = prev;
        prev = curr;
        curr = temp;
    }

    fprintf(fout, "%d\n", ans);

    return 0;
}
