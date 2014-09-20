#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    string str;
    cin >> n >> str;

    int ans = 0;
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) ans++;
    }

    cout << ans << endl;

    return 0;
}
