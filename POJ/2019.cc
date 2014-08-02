/*
 *  SRC: POJ 2019
 * PROB: Cornfields
 * ALGO: NULL
 * DATE: May 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

struct data {
    int max, min;
};

int main()
{
    int N, B, K;
    scanf("%d%d%d", &N, &B, &K);

    int map[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", map[i] + j);

    data r[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - B + 1; j++) {
            int max = map[i][j], min = map[i][j];
            for (int k = j + 1; k < j + B; k++) {
                if (map[i][k] > max) max = map[i][k];
                if (map[i][k] < min) min = map[i][k];
            }
            r[i][j].max = max;
            r[i][j].min = min;
        }

    while (K--) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        int max = r[a][b].max, min = r[a][b].min;
        for (int i = a + 1; i < a + B; i++) {
            if (r[i][b].max > max) max = r[i][b].max;
            if (r[i][b].min < min) min = r[i][b].min;
        }
        printf("%d\n", max - min);
    }

    return 0;
}

