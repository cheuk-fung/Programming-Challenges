/*
 *  SRC: HDOJ 3831
 * PROB: DICS
 * ALGO: DP
 * DATE: Apr 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

int f[510][510][55];

inline int c2id(char c)
{
    if (!isalpha(c)) return 52;
    if (c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

int main()
{
    string src, dest;
    while (cin >> src, src != "#") {
        cin >> dest;

        src = "." + src;
        dest = "." + dest;

        memset(f, 0x3f, sizeof(f));

        for (int k = 0; k <= 52; k++) {
            f[src.length()][dest.length()][k] = 0;
        }
        for (int i = src.length() - 1; i >= 0; i--) {
            for (int k = 0; k <= 52; k++) {
                f[i][dest.length()][k] = f[i + 1][dest.length()][k] + 1;
            }
        }
        for (int j = dest.length() - 1; j >= 0; j--) {
            for (int k = 0; k <= 52; k++) {
                f[src.length()][j][k] = f[src.length()][j + 1][k] + 1;
            }
        }

        for (int i = src.length() - 1; i >= 0; i--) {
            for (int j = dest.length() - 1; j >= 0; j--) {
                for (int k = 0; k <= 52; k++) {
                    if (k == c2id(dest[j]) || (k == 52 && src[i] == dest[j])) {
                        f[i][j][k] = min(f[i + 1][j + 1][k], f[i + 1][j + 1][c2id(dest[j + 1])] + 1);
                    } else {
                        int a = min(min(f[i + 1][j][k], f[i][j + 1][k]), f[i + 1][j + 1][k]) + 1;
                        int b = min(min(f[i + 1][j][c2id(dest[j])], f[i][j + 1][c2id(dest[j + 1])]), f[i + 1][j + 1][c2id(dest[j + 1])]) + 2;
                        f[i][j][k] = min(a, b);
                    }
                }
            }
        }

        cout << f[0][0][52] << endl;
    }

    return 0;
}

