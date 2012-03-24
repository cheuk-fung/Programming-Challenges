#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 10000010;

int f[2][4];

int main()
{
    int n;
    while (cin >> n) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        int *prev = f[0];
        int *curr = f[1];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 4; j++) {
                curr[j] = 0;
                for (int k = 0; k < 4; k++) {
                    if (k == j) continue;
                    curr[j] = (curr[j] + prev[k]) % MOD;
                }
            }
            int *temp = curr;
            curr = prev;
            prev = temp;
        }

        cout << prev[0] << endl;
    }

    return 0;
}

