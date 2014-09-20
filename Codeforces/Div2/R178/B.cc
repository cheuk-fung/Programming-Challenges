#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> book[2];

void work(int id)
{
    sort(book[id].begin(), book[id].end());
    for (int i = 1; i < (int)book[id].size(); i++) {
        book[id][i] += book[id][i - 1];
    }
}

int main()
{
    int n;
    cin >> n;

    int tot = 0;
    book[0].push_back(0);
    book[1].push_back(0);
    for (int i = 0; i < n; i++) {
        int t, w;
        cin >> t >> w;
        book[t - 1].push_back(w);
        tot += t;
    }

    work(0);
    work(1);

    int ans = tot;
    for (int i = 1; i <= (int)book[0].size(); i++) {
        for (int j = 1; j <= (int)book[1].size(); j++) {
            int now = book[0].size() - i + 2 * (book[1].size() - j);
            if (book[0][i - 1] + book[1][j - 1] <= now) {
                ans = min(ans, now);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
