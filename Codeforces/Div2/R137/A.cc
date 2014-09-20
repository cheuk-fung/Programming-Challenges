#include <iostream>
#include <cstdio>

using namespace std;

int a[100010];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    int back = n - 1;
    while (back > 0 && a[back - 1] == a[back]) back--;
    if (back < k) {
        cout << back << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
