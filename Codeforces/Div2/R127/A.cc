#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    char c = *max_element(s.begin(), s.end());
    int cnt = count(s.begin(), s.end(), c);
    while (cnt--) cout << c;
    cout << endl;

    return 0;
}

