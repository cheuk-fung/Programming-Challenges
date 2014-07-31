#include <iostream>
#include <functional>
#include <vector>
#include <queue>

using namespace std;

int n, k;
long long b;
int a[100010];

int main()
{
    while (cin >> n >> k >> b) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int ans = n;
        long long tot = 0;
        priority_queue< int, vector<int>, greater<int> > que;
        for (int i = n - 2; i >= 0; i--) {
            if (tot + a[i] > b) ans = i + 1;
            que.push(a[i]);
            tot += a[i];
            if (que.size() == k) {
                tot -= que.top();
                que.pop();
            }
        }

        cout << ans << endl;
    }

    return 0;
}

