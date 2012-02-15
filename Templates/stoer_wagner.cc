/*
 *  SRC: HDOJ 3691
 * PROB: Nubulsa Expo
 * ALGO: Stoer-Wagner
 * DATE: Oct 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int inf = 0x3f3f3f3f;
const int MAXN = 333;

int n, m;
int map[MAXN][MAXN];

bool A[MAXN];
int v[MAXN], w[MAXN];

int stoer_wagner(int n)
{
    int res = inf;
    for (int i = 0; i < n; i++) v[i] = i;

    while (n > 1) {
        A[v[0]] = true;

        for (int i = 1; i < n; i++) {
            A[v[i]] = false;
            w[v[i]] = map[v[0]][v[i]];
        }

        for (int prev = 0, i = 1; i < n; i++) {
            int curr = -1;
            for (int j = 1; j < n; j++)
                if (!A[v[j]] && (curr == -1 || w[v[j]] > w[v[curr]]))
                    curr = j;
            A[v[curr]] = true;

            if (i == n - 1) {
                if (res > w[v[curr]]) res = w[v[curr]];
                for (int j = 0; j < n; j++)
                    map[v[j]][v[prev]] = map[v[prev]][v[j]] += map[v[curr]][v[j]];
                v[curr] = v[--n];
                break;
            }

            prev = curr;
            for (int j = 1; j < n; j++)
                if (!A[v[j]]) w[v[j]] += map[v[curr]][v[j]];
        }
    }

    return res;
}

int main()
{
    while (scanf("%d%d%*d", &n, &m), n && m) {
        memset(map, 0, sizeof(map));

        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--, b--;
            map[a][b] = map[b][a] += c;
        }
        
        printf("%d\n", stoer_wagner(n));
    }

    return 0;
}
