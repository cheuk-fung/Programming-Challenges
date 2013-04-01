#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string s;
    int p;
    cin >> s >> p;
    for (int i = 0; i < (int)s.length(); i++) {
        if (isupper(s[i])) s[i] = tolower(s[i]);
        if (s[i] < p + 97) {
            cout << (char)toupper(s[i]);
        } else {
            cout << (char)tolower(s[i]);
        }
    }
    cout << endl;

    return 0;
}
