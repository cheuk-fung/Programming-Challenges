#include <iostream>

using namespace std;

bool digit[10];

int main()
{
    int n;
    cin >> n;
    int t = n;
    while (t) {
        digit[t % 10] = true;
        t /= 10;
    }

    int cnt = 0;
    for (int i = 1; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            int t = i;
            bool ok = false;
            while (t) {
                if (digit[t % 10]) {
                    ok = true;
                    break;
                }
                t /= 10;
            }
            if (ok) cnt++;

            t = n / i;
            if (t == i) continue;
            ok = false;
            while (t) {
                if (digit[t % 10]) {
                    ok = true;
                    break;
                }
                t /= 10;
            }
            if (ok) cnt++;
        }
    }
    cout << cnt << endl;

    return 0;
}
