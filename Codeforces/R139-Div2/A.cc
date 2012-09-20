#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int top;
    cin >> top;
    int bottom = 7 - top;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int vis[7];
        memset(vis, 0, sizeof vis);
        vis[bottom] = vis[a] = vis[b] = vis[7 - a] = vis[7 - b] = true;
        int cnt = 0;
        for (int j = 1; j <= 6; j++) {
            if (!vis[j]) {
                cnt++;
                top = j;
            }
        }
        if (cnt > 1) {
            cout << "NO" << endl;
            return 0;
        }
        bottom = 7 - top;
    }

    cout << "YES" << endl;

    return 0;
}

