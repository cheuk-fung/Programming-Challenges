/*
 *  SRC: ZOJ 3603
 * PROB: Draw Something Cheat
 * ALGO: NULL
 * DATE: Apr 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int cnt[256][30];

int main()
{
    int tasks;
    cin >> tasks;
    while (tasks--) {
        int n;
        cin >> n;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < s.length(); j++) {
                cnt[s[j]][i]++;
            }
        }

        for (int c = 'A'; c <= 'Z'; c++) {
            int times = *min_element(cnt[c], cnt[c] + n);
            while (times--) {
                cout << (char)c;
            }
        }
        cout << endl;
    }

    return 0;
}

