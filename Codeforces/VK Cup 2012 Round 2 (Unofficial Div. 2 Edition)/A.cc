#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, a, b;
    int h[2011];
    while (cin >> n >> a >> b) {
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        sort(h, h + n);
        cout << h[b] - h[b - 1] << endl;
    }

    return 0;
}

