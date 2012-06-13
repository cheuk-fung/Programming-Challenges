#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        string ans;
        int pos = 0;
        char mx;
        do {
            mx = *max_element(s.begin() + pos, s.end());
            for (int i = pos; i < s.length(); i++) {
                if (s[i] == mx) {
                    ans += mx;
                    pos = i + 1;
                }
            }
        } while (pos != s.length()) ;
        cout << ans << endl;
    }

    return 0;
}

