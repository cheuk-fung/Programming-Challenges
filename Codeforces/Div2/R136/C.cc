#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;
int n, a[MAXN], b[MAXN];

bool check()
{
    sort(b, b + n);
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            l = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            r = i;
            break;
        }
    }

    if (l == -1 && r == -1) return true;
    swap(b[l], b[r]);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main()
{
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            b[i] = a[i];
        }
        cout << (check() ? "YES" : "NO") << endl;
    }

    return 0;
}
