#include <iostream>
#include <string>

using namespace std;

string s;
char restriction[256];

int main()
{
    cin >> s;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        char a, b;
        cin >> a >> b;
        restriction[a] = b;
        restriction[b] = a;
    }

    int cnt = 0;
    for (int i = 1; i < s.length(); i++)
        if (restriction[s[i]] == s[i - 1]) {
            int l = 0, r = 0;
            char a = s[i - 1], b = s[i];
            for (int j = i - 1; j >= 0; j--) {
                if (s[j] == a) l++;
                else if (s[j] == b) r++;
                else break;
            }
            for ( ; i < s.length(); i++) {
                if (s[i] == a) l++;
                else if (s[i] == b) r++;
                else break;
            }
            cnt += min(l, r);
        }

    cout << cnt << endl;

    return 0;
}

