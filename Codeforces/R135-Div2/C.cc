#include <iostream>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;
template<class T> inline int SIZE(const T &x) { return x.size(); }

const int MAXN = 5 * 1e5 + 10;

int f[MAXN][30];
int g[MAXN][30];

int main()
{
    int n, k;
    string s;
    cin >> n >> k >> s;
    for (int i = 0; i < k; i++) {
        f[0][i] = 1;
    }
    f[0][s[0] - 'A'] = 0;
    for (int i = 1; i < SIZE(s); i++) {
        for (int j = 0; j < k; j++) {
            f[i][j] = INF;
            for (int l = 0; l < k; l++) {
                if (j == l) continue;
                if (f[i - 1][l] < f[i][j]) {
                    f[i][j] = f[i - 1][l];
                    g[i][j] = l;
                }
            }
            if (j != s[i] - 'A') f[i][j]++;
        }
    }
    int ans = INF;
    int prev;
    string as;
    for (int j = 0; j < k; j++) {
        if (f[SIZE(s) - 1][j] < ans) {
            ans = f[SIZE(s) - 1][j];
            prev = j;
        }
    }
    cout << ans << endl;

    as += (char)(prev + 'A');
    for (int i = SIZE(s) - 1; i > 0; i--) {
        prev = g[i][prev];
        as += (char)(prev + 'A');
    }
    for (int i = SIZE(as) - 1; i >= 0; i--) cout << as[i];
    cout << endl;

    return 0;
}

