#include <cstdio>
#include <iostream>
#include <string>
#include <set>

using namespace std;

const int MOD = 1000000007;
typedef set<string>::iterator si;

int main()
{
    int n, m;
    cin >> n >> m;
    set<string> name;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        name.insert(s);
    }

    long long ans = 1;
    for (int i = 0; i < m; i++) {
        set<char> c;
        for (si it = name.begin(); it != name.end(); it++)
            c.insert((*it)[i]);
        ans = ans * c.size() % MOD;
    }

    cout << ans << endl;

    return 0;
}

