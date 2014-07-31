#include <iostream>
#include <vector>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

vector<int> ans;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    if (k == 1) {
        for (int i = 1; i <= n + m; i += n - 1) {
            ans.push_back(i);
        }
    } else {
        for (int i = 0; i < k; i++) {
            ans.push_back(1);
        }
        ans.push_back(n);
        for (int i = 1; i < k; i++) {
            ans.push_back(n + 1);
        }
        if (n == m) ans.push_back(n + m);
    }
    cout << SIZE(ans) << endl;
    for (int i = 0; i < SIZE(ans); i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}

