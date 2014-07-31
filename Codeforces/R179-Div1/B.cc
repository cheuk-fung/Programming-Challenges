#include <iostream>
#include <algorithm>

using namespace std;

long long mat[555][555], mat_r[555][555];
long long ans[555];
int x[555];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        x[i]--;
    }

    reverse(x, x + n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < i; k++) {
            for (int j = 0; j < i; j++) {
                mat[x[i]][x[k]] = min(mat[x[i]][x[k]], mat[x[i]][x[j]] + mat[x[j]][x[k]]);
                mat[x[k]][x[i]] = min(mat[x[k]][x[i]], mat[x[k]][x[j]] + mat[x[j]][x[i]]);
            }
        }

        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                mat[x[j]][x[k]] = min(mat[x[j]][x[k]], mat[x[j]][x[i]] + mat[x[i]][x[k]]);
            }
        }

        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= i; k++) {
                ans[i] += mat[x[j]][x[k]];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << ans[i] << endl;
    }

    return 0;
}
