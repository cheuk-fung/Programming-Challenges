#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

int N;
char s[222];
bool f[1 << 20];
double g[1 << 20];

double dp(int now)
{
    if (f[now]) return g[now];

    f[now] = true;
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            int s = 1 << ((j + k) % N);
            if (now & s) continue;
            g[now] += dp(now | s) + N - k;
            break;
        }
    }

    return g[now] /= N;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int task = 1; task <= T; task++) {
        printf("Case #%d: ", task);

        scanf("%s", s);
        N = strlen(s);
        reverse(s, s + N);
        int now = 0;
        for (int i = 0; i < N; i++) {
            now <<= 1;
            if (s[i] == 'X') now++;
        }

        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        f[(1 << N) - 1] = true;
        double ans = dp(now);

        printf("%.10f\n", ans);
    }

    return 0;
}
