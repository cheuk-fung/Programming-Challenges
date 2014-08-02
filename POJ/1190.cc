/*
 *  SRC: POJ 1190
 * PROB: 生日蛋糕
 * ALGO: DFS
 * DATE: Jul 15, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

int n, m;
int ans = 0x7FFFFFFF;

inline int vol(int r, int h)
{
    return r * r * h;
}

inline int spa(int r, int h)
{
    return 2 * r * h;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void dfs(int v, int s, int d, int preR, int preH)
{
    if (d == m) {
        if (v == n && s < ans) ans = s;
        return ;
    }

    int minR = m - d;
    int minH = m - d;

    for (int i = preR - 1; i >= minR; i--) {
        int maxH = min(preH, (n - v) / (i * i) + 1);
        for (int j = maxH - 1; j >= minH; j--) {
            int newV = v + vol(i, j);
            int resV = n - newV;
            if (resV < 0) break;

            int newS = s + spa(i, j);
            if (d == 0) newS += i * i;
            if (newS + 2 * resV / i >= ans) break;

            dfs(newV, newS, d + 1, i, j);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    dfs(0, 0, 0, n, n);

    if (ans == 0x7FFFFFFF) ans = 0;
    printf("%d\n", ans);

    return 0;
}
