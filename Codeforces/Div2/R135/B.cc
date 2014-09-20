#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

int main()
{
    long long p, d;
    string s;
    cin >> s >> d;
    istringstream is(s);
    is >> p;
    for (int i = 0; i < SIZE(s) - 1; i++) {
        long long t = 0;
        for (int j = 0; j <= i; j++) {
            t = t * 10 + s[j] - '0';
        }
        long long x = t--;
        for (int j = i + 1; j < SIZE(s); j++) {
            x = x * 10 + 9;
            t = t * 10 + 9;
        }
        if (x == p) {
            cout << x << endl;
            return 0;
        }
        if (p - t <= d) {
            cout << t << endl;
            return 0;
        }
    }
    cout << p << endl;

    return 0;
}

