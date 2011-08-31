/*
 *  SRC: POJ 1185
 * PROB: 炮兵阵地
 * ALGO: DP
 * DATE: Aug 31, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

int n, m, best;
int map[110], f[2][100][100];
int way_cnt, way[110], bit_cnt[110];
int curr = 0, next = 1;

void generate_way(int c, int curr_way, int cnt)
{
    if (c >= m) {
        way[way_cnt] = curr_way;
        bit_cnt[way_cnt++] = cnt;
        return ;
    }

    bool can_put = 1;
    if (c > 0 && (curr_way & 1 << (c - 1))) can_put = 0;
    if (c > 1 && (curr_way & 1 << (c - 2))) can_put = 0;
    if (can_put)
        generate_way(c + 3, curr_way | (1 << c), cnt + 1);
    generate_way(c + 1, curr_way, cnt);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        char str[m + 1];
        scanf("%s", str);
        for (int j = 0; j < m; j++) {
            map[i] <<= 1;
            if (str[j] == 'H') map[i]++;
        }
    }

    generate_way(0, 0, 0);

    memset(f, 0xff, sizeof(f));
    f[curr][0][0] = 0;

    // the first line
    for (int i = 0; i < way_cnt; i++)
        if (!(map[0] & way[i])) {
            f[next][i][0] = bit_cnt[i];
            best = max(best, f[next][i][0]);
        }
    curr ^= 1;
    next ^= 1;
    memset(f[next], 0xff, sizeof(f[next]));

    // the second line
    if (n > 1)
        for (int i = 0; i < way_cnt; i++) {
            if (map[0] & way[i]) continue;
            for (int j = 0; j < way_cnt; j++) {
                if (map[1] & way[j]) continue;
                if (way[i] & way[j]) continue;
                f[next][j][i] = max(f[next][j][i], f[curr][i][0] + bit_cnt[j]);
                best = max(best, f[next][j][i]);
            }
        }
    curr ^= 1;
    next ^= 1;
    memset(f[next], 0xff, sizeof(f[next]));

    for (int i = 2; i < n; i++) {
        for (int j = 0; j < way_cnt; j++) {
            if (map[i - 2] & way[j]) continue;
            for (int k = 0; k < way_cnt; k++) {
                if (map[i - 1] & way[k]) continue;
                if (way[j] & way[k]) continue;
                for (int l = 0; l < way_cnt; l++) {
                    if (map[i] & way[l]) continue;
                    if (way[j] & way[l]) continue;
                    if (way[k] & way[l]) continue;
                    f[next][l][k] = max(f[next][l][k], f[curr][k][j] + bit_cnt[l]);
                    best = max(best, f[next][l][k]);
                }
            }
        }
        curr ^= 1;
        next ^= 1;
        memset(f[next], 0xff, sizeof(f[next]));
    }

    printf("%d\n", best);

    return 0;
}
