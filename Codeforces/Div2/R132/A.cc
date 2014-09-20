#include <iostream>
#include <algorithm>

using namespace std;

int a[100], b[100];

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int mx = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[j] % a[i] == 0) {
                if (b[j] / a[i] > mx) {
                    mx = b[j] / a[i];
                    cnt = 1;
                } else if (b[j] / a[i] == mx) {
                    cnt++;
                }
            }
        }
    }

    cout << cnt << endl;

    return 0;
}
