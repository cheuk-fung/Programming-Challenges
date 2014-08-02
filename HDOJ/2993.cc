/*
 *  SRC: HDOJ 2993
 * PROB: MAX Average Problem
 * ALGO: DP
 * DATE: Aug 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cctype>

const int MAXN = 1e5 + 10;

struct Node {
    long long x, y;
} que[MAXN];
long long sum[MAXN];

template<typename T> inline T MAX(T x, T y) { return x > y ? x : y; }

int nextint()
{
    char c;
    while (isspace(c = getchar())) ;

    int res = c - '0';
    while (isdigit(c = getchar())) res = res * 10 + c - '0';
    return res;
}

inline long long cross(const Node &a, const Node &b, const Node &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nextint();
        }

        int head = 0, tail = 0;
        double ans = 0;
        for (int i = k; i <= n; i++) {
            Node now = {i - k, sum[i - k]};
            while (head + 1 < tail && cross(que[tail - 2], que[tail - 1], now) <= 0) tail--;
            que[tail++] = now;

            now.x = i; now.y = sum[i];
            while (head + 1 < tail && cross(que[head], que[head + 1], now) >= 0) head++;
            ans = MAX(ans, (double)(sum[i] - que[head].y) / (i - que[head].x));
        }

        printf("%.2f\n", ans);
    }

    return 0;
}

