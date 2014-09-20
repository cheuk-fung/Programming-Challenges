#include <iostream>
#include <cstdio>

using namespace std;

int mat[5010][5010];
int row[5010], col[5010];

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < n; i++) row[i] = i;
    for (int i = 0; i < m; i++) col[i] = i;
    for (int i = 0; i < k; i++) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        if (c == 'c') {
            swap(col[x - 1], col[y - 1]);
        } else if (c == 'r') {
            swap(row[x - 1], row[y - 1]);
        } else {
            cout << mat[row[x - 1]][col[y - 1]] << endl;
        }
    }

    return 0;
}
