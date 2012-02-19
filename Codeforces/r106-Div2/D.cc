#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int MOD = 1000000007;

string seq;
int match[1000];
int f[1000][1000][3][3]; // f[left][right][left_color][right_color]
stack<int> bracket;

long long dp(int l, int r, int lc, int rc)
{
    if (f[l][r][lc][rc] != -1) return f[l][r][lc][rc];

    long long res = 0;

    if (match[l] == r) {
        if (!lc && !rc) return f[l][r][lc][rc] = 0;
        if ( lc &&  rc) return f[l][r][lc][rc] = 0;
        if (l + 1 == r) return f[l][r][lc][rc] = 1;

        for (int i = 0; i < 3; i++) {
            if (lc && i == lc) continue;
            for (int j = 0; j < 3; j++) {
                if (rc && j == rc) continue;
                res = (res + dp(l + 1, r - 1, i, j)) % MOD;
            }
        }

        return f[l][r][lc][rc] = res;
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (i && j && i == j) continue;
            res = (res + dp(l, match[l], lc, i) * dp(match[l] + 1, r, j, rc)) % MOD;
        }

    return f[l][r][lc][rc] = res;
}

int main()
{
    cin >> seq;
    for (int i = 0; i < seq.length(); i++) {
        if (seq[i] == '(') bracket.push(i);
        else {
            match[bracket.top()] = i;
            match[i] = bracket.top();
            bracket.pop();
        }
    }

    memset(f, 0xff, sizeof(f));

    int ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ans = (ans + dp(0, seq.length() - 1, i, j)) % MOD;

    printf("%d\n", ans);

    return 0;
}
