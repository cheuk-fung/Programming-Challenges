#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int n;
int f[256][256];

int main()
{
    while (cin >> n) {
        memset(f, 0, sizeof(f));

        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            int first = *name.begin(), last = *name.rbegin();
            for (int j = 'a'; j <= 'z'; j++) {
                if (f[j][first] || j == first) {
                    f[j][last] = max(f[j][last], f[j][first] + (int)name.length());
                }
            }
        }

        int ans = 0;
        for (int i = 'a'; i <= 'z'; i++) {
            ans = max(ans, f[i][i]);
        }
        cout << ans << endl;
    }

    return 0;
}

