#include <iostream>

using namespace std;

int gpow(long long a, long long b, long long mod)
{
    long long r = 1;
    while (b) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

int main()
{
    int n, m;
    while (cin >> n >> m) {
        cout << ((gpow(3, n, m) - 1) % m + m) % m << endl;
    }

    return 0;
}

