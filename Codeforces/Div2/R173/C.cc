#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool work()
{
    string s, t;
    cin >> s >> t;
    if (s == t) return true;
    if (s.length() != t.length()) return false;
    if (count(s.begin(), s.end(), '0') == s.length() || count(t.begin(), t.end(), '0') == t.length()) return false;
    return true;
}

int main()
{
    cout << (work() ? "YES" : "NO") << endl;

    return 0;
}
