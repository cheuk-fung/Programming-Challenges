#include <iostream>

using namespace std;

int main()
{
    int n, k;
    while (cin >> n >> k) {
        k -= n << 1;
        if (k >= n) cout << 0 << endl;
        else cout << n - k << endl;
    }

    return 0;
}

