#include <iostream>

using namespace std;

int main()
{
    int n, x, y;
    while (cin >> n >> x >> y) {
        int tot = y * n / 100;
        if (y * n % 100) tot++;
        cout << max(tot - x, 0)  << endl;
    }

    return 0;
}

