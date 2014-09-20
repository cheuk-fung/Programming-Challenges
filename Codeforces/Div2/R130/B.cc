#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 55;

bool f[MAXN][MAXN][MAXN][MAXN];
char card[MAXN][5];

int idx(char *s)
{
    int c;
    switch (s[0]) {
        case 'A': c = 0; break;
        case 'T': c = 9; break;
        case 'J': c = 10; break;
        case 'Q': c = 11; break;
        case 'K': c = 12; break;
        default: c = s[0] - '0' - 1;
    }

    int k;
    switch (s[1]) {
        case 'S': k = 0; break;
        case 'D': k = 1; break;
        case 'H': k = 2; break;
        case 'C': k = 3;
    }

    return k * 13 + c;
}

inline int same(int x, int y) { return x / 13 == y / 13 || x % 13 == y % 13; }

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> card[i];
    }

    f[n - 1][idx(card[n - 1])][52][52] = true;
    if (n > 1) f[n - 2][idx(card[n - 2])][idx(card[n - 1])][52] = true;
    if (n > 2) f[n - 3][idx(card[n - 3])][idx(card[n - 2])][idx(card[n - 1])] = true;
    for (int a = n - 2; a >= 0; a--) {
        int i = idx(card[a]);
        for (int j = 0; j < 52; j++) {
            if (f[a + 1][j][52][52] && same(i, j)) {
                f[a][j][52][52] = true;
            }
            for (int k = 0; k < 52; k++) {
                if (f[a + 1][j][k][52] && same(j, k)) {
                    f[a][i][k][52] = true;
                }
                for (int l = 0; l < 52; l++) {
                    if (f[a + 1][j][k][l] && same(k, l)) {
                        f[a][i][j][l] = true;
                    }
                    if (f[a + 1][j][k][l] && same(i, l)) {
                        f[a][l][j][k] = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 52; i++) {
        if (f[0][i][52][52]) {
            cout << "YES" << endl;
            return 0;
        }
        for (int j = 0; j < 52; j++) {
            if (f[0][i][j][52] && same(i, j)) {
                cout << "YES" << endl;
                return 0;
            }
            for (int k = 0; k < 52; k++) {
                if (f[0][i][j][k] && same(j, k) && same(i, k)) {
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
    }

    cout << "NO" << endl;

    return 0;
}
