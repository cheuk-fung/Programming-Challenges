/*
 *  SRC: HDOJ 4395
 * PROB: D-mail
 * ALGO: DP
 * DATE: Aug 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int offset = 210000;

bool dp[offset << 1];

int get_num(char *s)
{
    int sig = 1;
    char *t = s;
    if (t[0] == '-') {
        sig = -1;
        t++;
    }
    int a, b;
    sscanf(t, "%d.%d", &a, &b);
    return sig * (a * 10000 + b);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(dp, 0, sizeof dp);

        char s[10];
        int n;
        scanf(" %s %d", s, &n);
        int m = get_num(s);
        bool *f = &dp[offset];
        f[0] = true;
        vector<int> positive, negtive;
        for (int i = 0; i < n; i++) {
            scanf(" %s", s);
            int a = get_num(s);
            if (a > 0) positive.push_back(a);
            else if (a < 0) negtive.push_back(a);
        }
        for (int i = 0; i < (int)negtive.size(); i++) {
            int a = negtive[i];
            for (int j = -offset; j <= 0; j++) {
                if (f[j - a]) f[j] = true;
            }
        }
        for (int i = 0; i < (int)positive.size(); i++) {
            int a = positive[i];
            for (int j = 20000 - 1; j >= -offset + a; j--) {
                if (f[j - a]) f[j] = true;
            }
        }

        int ans = -offset;
        for (int i = -offset; i < 20000; i++) {
            if (f[i] && abs(m - i) < abs(m - ans)) {
                ans = i;
            }
        }

        printf("%.4f\n", ans / 10000.0);
    }

    return 0;
}

