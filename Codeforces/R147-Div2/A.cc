#include <iostream>
#include <algorithm>
#include <utility>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef map<pii, int>::const_iterator mci;

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    map<pii, int> cnt;
    for (int i = 0; i < n; i++) {
        pii now;
        cin >> now.first >> now.second;
        cnt[now]++;
    }

    int ans = 0;
    for (mci it = cnt.begin(); it != cnt.end(); it++) ans = max(ans, it->second);
    cout << ans << endl;

    return 0;
}

