/*
 *  SRC: HDOJ 3711
 * PROB: Binary Number
 * ALGO: NULL
 * DATE: Oct 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <string>

using std::string;

int n, m;
int a[200], b;
string a_bin[200], b_bin;

string change_to_bin(int x)
{
    string res;
    while (x) {
        if (x & 1) res += "1";
        else res += "0";
        x >>= 1;
    }
    while (res.length() < 32) res += "0";
    return res;
}

int solve()
{
    int res, min_f = 0x3f3f3f3f;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < b_bin.length(); j++)
            if (a_bin[i][j] != b_bin[j]) cnt++;
        if (cnt < min_f) {
            min_f = cnt;
            res = a[i];
        }
        else if (cnt == min_f && a[i] < res)
            res = a[i];
    }
    return res;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        for (int i = 0; i < n; i++)
            a_bin[i] = change_to_bin(a[i]);
        for (int i = 0; i < m; i++) {
            scanf("%d", &b);
            b_bin = change_to_bin(b);
            printf("%d\n", solve());
        }
    }

    return 0;
}
