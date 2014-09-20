#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int main()
{
    int n, d;
    while (cin >> n >> d) {
        int a, b;
        cin >> a >> b;

        vector<pii> client;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            client.push_back(pii(x * a + y * b, i + 1));
        }
        sort(client.begin(), client.end());

        int cnt = 0;
        while (d >= client[cnt].first && cnt < n) {
            d -= client[cnt++].first;
        }
        cout << cnt << endl;
        for (int i = 0; i < cnt; i++) cout << client[i].second << " ";
        cout << endl;
    }

    return 0;
}

