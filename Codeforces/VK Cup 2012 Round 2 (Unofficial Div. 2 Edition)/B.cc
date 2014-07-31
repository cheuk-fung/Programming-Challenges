#include <cstring>
#include <iostream>
#include <string>

using namespace std;

string a, s;
int cnt[10];

int main()
{
    while (cin >> a >> s) {
        int n = a.length();
        int m = s.length();

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < m; i++) {
            cnt[s[i] - '0']++;
        }

        for (int i = 0, j = 9; i < n; i++) {
            while (cnt[j] == 0) {
                j--;
                if (j < 0) break;
            }
            if (j < 0) break;

            if (a[i] < j + '0') {
                a[i] = j + '0';
                cnt[j]--;
            }
        }

        cout << a << endl;
    }

    return 0;
}

