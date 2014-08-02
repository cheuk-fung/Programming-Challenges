/*
 *  SRC: NKOJ 1081
 * PROB: All in all
 * ALGO: String
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>

using namespace std;

string s, t;

int main()
{
    while (cin >> s >> t) {
        int cnt = 0;
        for (int i = 0; i < t.length(); i++)
            if (s[cnt] == t[i]) cnt++;
        if (cnt == s.length()) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
