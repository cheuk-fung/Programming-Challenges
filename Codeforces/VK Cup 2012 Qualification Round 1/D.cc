#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 20010;

int degree[MAXN];

int main()
{
    int n;
    int ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> degree[i];
        ans += degree[i];
    }

    for (int i = 3, loop_end = n / 2 + 1; i < loop_end; i++) {
        if (n % i) continue;
        for (int j = 0, gap = n / i; j < gap; j++) {
            int curr = 0;
            for (int k = j; k < n; k += gap) curr += degree[k];
            ans = max(ans, curr);
        }
    }

    cout << ans << endl;

    return 0;
}

