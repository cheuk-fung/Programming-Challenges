#include <iostream>
#include <map>

using namespace std;

int lsum[100010];
map<int, int> cnt;

int main()
{
    int k, b, n;
    cin >> k >> b >> n;

    long long zerocnt = 0;
    long long zero = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        lsum[i] = (lsum[i - 1] + a) % (k - 1);
        if (a == 0) {
            zero++;
        } else {
            zerocnt += (zero + 1) * zero / 2;;
            zero = 0;
        }
    }
    zerocnt += (zero + 1) * zero / 2;
    if (b == 0) {
        cout << zerocnt << endl;
    } else {
        long long now = 0;
        for (int i = 0; i <= n; i++) {
            now += cnt[lsum[i]];
            cnt[(lsum[i] + b) % (k - 1)]++;
        }
        if (b == k - 1) {
            cout << now - zerocnt << endl;
        } else {
            cout << now << endl;
        }
    }

    return 0;
}

