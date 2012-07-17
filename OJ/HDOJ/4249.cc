/*
 *  SRC: HDOJ 4249
 * PROB: A Famous Equation
 * ALGO: DP
 * DATE: Jul 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

long long f[10][2];

int main()
{
    int task = 1;
    string s;
    while (cin >> s) {
        int add = s.find('+');
        int equal = s.find('=');
        string a = s.substr(0, add);
        string b = s.substr(add + 1, equal - add - 1);
        string c = s.substr(equal + 1);

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        reverse(c.begin(), c.end());

        f[0][0] = 1;
        f[0][1] = 0;
        int max_length = max(a.length(), max(b.length(), c.length()));
        for (int n = 0; n < max_length; n++) {
            char x = n >= a.length() ? '0' : a[n];
            char y = n >= b.length() ? '0' : b[n];
            char z = n >= c.length() ? '0' : c[n];

            int stx = n + 1 == a.length() && n > 0 ? 1 : 0, edx = 9;
            int sty = n + 1 == b.length() && n > 0 ? 1 : 0, edy = 9;
            int stz = n + 1 == c.length() && n > 0 ? 1 : 0, edz = 9;
            if (x != '?') stx = edx = x - '0';
            if (y != '?') sty = edy = y - '0';
            if (z != '?') stz = edz = z - '0';

            f[n + 1][0] = f[n + 1][1] = 0;
            for (int i = stx; i <= edx; i++) {
                for (int j = sty; j <= edy; j++) {
                    for (int k = stz; k <= edz; k++) {
                        for (int m = 0; m < 2; m++) {
                            if ((i + j + m) % 10 == k) {
                                f[n + 1][(i + j + m) / 10] += f[n][m];
                            }
                        }
                    }
                }
            }
        }

        cout << "Case " << task++ << ": " << f[max_length][0] << endl;
    }

    return 0;
}

