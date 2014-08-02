/*
 *  SRC: HDOJ 4357
 * PROB: String change
 * ALGO: NULL
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        cout << "Case #" << task << ": ";

        string s, t;
        cin >> s >> t;
        if (s.length() <= 2) {
            bool meet = false;
            for (int i = 0; i <= 24; i++) {
                if (s == t) {
                    meet = true;
                    break;
                }
                swap(s[0], s[1]);
                s[0] = (s[0] - 'a' + 1) % 26 + 'a';
                s[1] = (s[1] - 'a' + 1) % 26 + 'a';
            }
            cout << (meet ? "YES" : "NO") << endl;
        } else {
            int a = 0, b = 0;
            for (int i = 0; i < (int)s.length(); i++) a += s[i];
            for (int i = 0; i < (int)t.length(); i++) b += t[i];
            cout << (((b - a) & 1) ? "NO" : "YES") << endl;
        }
    }

    return 0;
}

