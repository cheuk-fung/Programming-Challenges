/*
 *  SRC: POJ 3280
 * PROB: Cheapest Palindrome
 * ALGO: DP
 * DATE: Jul 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 2010;

string s;
int f[MAXN][MAXN];
int cost[256];

int dp(int l, int r)
{
    if (l >= r) return 0;
    if (f[l][r] != -1) return f[l][r];
    if (s[l] == s[r]) return f[l][r] = dp(l + 1, r - 1);
    return f[l][r] = min(cost[s[l]] + dp(l + 1, r), dp(l, r - 1) + cost[s[r]]);
}

int main()
{
    int n, m;
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < m; i++) {
        char c;
        int add, del;
        cin >> c >> add >> del;
        cost[c] = min(add, del);
    }
    memset(f, 0xff, sizeof(f));
    cout << dp(0, s.length() - 1) << endl;

    return 0;
}

