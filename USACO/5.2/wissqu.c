/*
ID: os.idea1
LANG: C
TASK: wissqu
*/
#include <stdio.h>

FILE *fin, *fout;

char map[5][6];
int cnt, cow['F'], vis[5][5];
int is_print = 1;

struct Point {
    char id;
    int x, y;
} ans[16];

inline int can_put(char c, int x, int y)
{
    if (vis[x][y]) return 0;

    int i, j;
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if (map[x + i][y + j] == c) return 0;

    return 1;
}

void print_ans()
{
    is_print = 0;
    
    int i;
    for (i = 0; i < 16; i++)
        fprintf(fout, "%c %d %d\n", ans[i].id, ans[i].x, ans[i].y);
}

void dfs(int p)
{
    if (p == 16) {
        cnt++;
        if (is_print) print_ans();

        return ;
    }

    char c;
    for (c = 'A'; c <= 'E'; c++)
        if (cow[c]) {
            int i, j;
            for (i = 1; i <= 4; i++)
                for (j = 1; j <= 4; j++)
                    if (can_put(c, i, j)) {
                        if (is_print) ans[p] = (struct Point){c, i, j};

                        char t = map[i][j];
                        map[i][j] = c;
                        cow[c]--;
                        vis[i][j] = 1;

                        dfs(p + 1);

                        vis[i][j] = 0;
                        cow[c]++;
                        map[i][j] = t;
                    }
        }
}

int main()
{
    fin = fopen("wissqu.in", "r");
    fout = fopen("wissqu.out", "w");

    int i, j;
    for (i = 1; i <= 4; i++) fscanf(fin, "%s", map[i] + 1);

    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            cow[map[i][j]]++;
    cow['D']++;
    cow['C']--;

    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            if (can_put('D', i, j)) {
                if (is_print) ans[0] = (struct Point){'D', i, j};

                char t = map[i][j];
                map[i][j] = 'D';
                cow['D']--;
                vis[i][j] = 1;

                dfs(1);

                vis[i][j] = 0;
                cow['D']++;
                map[i][j] = t;
            }

    fprintf(fout, "%d\n", cnt);

    return 0;
}
