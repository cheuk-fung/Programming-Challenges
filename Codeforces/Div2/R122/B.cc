#include <iostream>

using namespace std;

int f[] = {4, 1, 4, 2};

inline long long get(long long n)
{
    if (n == 1) return 3;
    return n * f[(n - 2) % 4] + 1;
}

int main()
{
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << get(n) << endl;
    }

    return 0;
}

