#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int dp2[333][333];
int dp3[333][333][333];

int main()
{
    int n;
    cin >> n;
    if (n == 1) {
        int a;
        cin >> a;
        cout << (a ? "BitLGM" : "BitAryo") << endl;
    } else if (n == 2) {
        memset(dp2, 0xff, sizeof dp2);

        int a, b;
        cin >> a >> b;

        dp2[0][0] = 0;
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= b; j++) {
                if (dp2[i][j] != -1) continue;
                for (int l = 0; l <= i; l++) {
                    if (dp2[l][j] == 0) {
                        dp2[i][j] = 1;
                        break;
                    }
                }
                if (dp2[i][j] == 1) continue;
                for (int l = 0; l <= j; l++) {
                    if (dp2[i][l] == 0) {
                        dp2[i][j] = 1;
                        break;
                    }
                }
                if (dp2[i][j] == 1) continue;
                int m = min(i, j);
                for (int l = 1; l <= m; l++) {
                    if (dp2[i - l][j - l] == 0) {
                        dp2[i][j] = 1;
                        break;
                    }
                }
                if (dp2[i][j] == 1) continue;
                dp2[i][j] = 0;
                for (int l = i + 1; l <= a; l++) {
                    dp2[l][j] = 1;
                }
                for (int l = j + 1; l <= b; l++) {
                    dp2[i][l] = 1;
                }
                for (int l = 1; i + l <= a && j + l <= b; l++) {
                    dp2[i + l][j + l] = 1;
                }
            }
        }
        cout << (dp2[a][b] ? "BitLGM" : "BitAryo") << endl;
    } else if (n == 3) {
        memset(dp3, 0xff, sizeof dp3);

        int a, b, c;
        cin >> a >> b >> c;

        dp3[0][0][0] = 0;
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= c; k++) {
                    if (dp3[i][j][k] != -1) continue;
                    for (int l = 0; l <= i; l++) {
                        if (dp3[l][j][k] == 0) {
                            dp3[i][j][k] = 1;
                            break;
                        }
                    }
                    if (dp3[i][j][k] == 1) continue;
                    for (int l = 0; l <= j; l++) {
                        if (dp3[i][l][k] == 0) {
                            dp3[i][j][k] = 1;
                            break;
                        }
                    }
                    if (dp3[i][j][k] == 1) continue;
                    for (int l = 0; l <= k; l++) {
                        if (dp3[i][j][l] == 0) {
                            dp3[i][j][k] = 1;
                            break;
                        }
                    }
                    if (dp3[i][j][k] == 1) continue;
                    int m = min(i, min(j, k));
                    for (int l = 1; l <= m; l++) {
                        if (dp3[i - l][j - l][k - l] == 0) {
                            dp3[i][j][k] = 1;
                            break;
                        }
                    }
                    if (dp3[i][j][k] == 1) continue;
                    dp3[i][j][k] = 0;
                    for (int l = i + 1; l <= a; l++) {
                        dp3[l][j][k] = 1;
                    }
                    for (int l = j + 1; l <= b; l++) {
                        dp3[i][l][k] = 1;
                    }
                    for (int l = k + 1; l <= c; l++) {
                        dp3[i][j][l] = 1;
                    }
                    for (int l = 1; i + l <= a && j + l <= b && k + l <= c; l++) {
                        dp3[i + l][j + l][k + l] = 1;
                    }
                }
            }
        }
        cout << (dp3[a][b][c] ? "BitLGM" : "BitAryo") << endl;
    }

    return 0;
}
