/*
 *  SRC: POJ
 * TASK: Constellations
 * ALGO: bit
 * DATE: 06/07/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int cases = 0;
int n, m, t, p ,q;
char map[1010][1010], buf[60];
long long star[60], sky[1010][10010];

bool check()
{

    for (int j = q - 1; j < m; j++)
        for (int i = 0; i + p - 1 < n; i++) {
            bool flag = true;
            for (int k = 0; k < p; k++)
                if (sky[j][i + k] != star[k]) {
                    flag = false;
                    break;
                }
            if (flag) return true;
        }

    return false;
}

bool work()
{
    scanf("%d%d%d%d%d", &n, &m, &t, &p, &q);
    if (n + m + t + p + q == 0) return false;
    gets(buf);

    for (int i = 0; i < n; i++) gets(map[i]);

    for (int i = 0; i < n; i++) {
        sky[q - 1][i] = 0;
        for (int j = 0; j < q; j++) {
            sky[q - 1][i] <<= 1;
            if (map[i][j] == '*') sky[q - 1][i]++;
        }
    }

    long long eps = (1LL << (q - 1)) - 1;
    for (int i = 0; i < n; i++) {
        for (int j = q; j < m; j++) {
            sky[j][i] = (sky[j - 1][i] & eps) << 1;
            if (map[i][j] == '*') sky[j][i]++;
        }
    }

    int cnt = 0;
    for (int i = 0; i < t; i++) {
        gets(buf);
        for (int j = 0; j < p; j++) {
            star[j] = 0;
            gets(buf);
            for (int k = 0; k < q; k++) {
                star[j] <<= 1;
                if (buf[k] == '*') star[j]++;
            }
        }
        if (check()) cnt++;
    }

    printf("Case %d: %d\n", ++cases, cnt);

    return true;
}

int main()
{
    while (work()) ;

    return 0;
}

