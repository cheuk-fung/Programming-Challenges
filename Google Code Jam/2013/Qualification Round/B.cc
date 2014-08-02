#include <iostream>

using namespace std;

int n, m;
int mat[111][111];

bool check()
{
    for (int h = 1; h <= 100; h++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] != h) continue;

                bool row = true;
                for (int k = 0; k < m; k++) {
                    row &= mat[i][k] <= h;
                }

                bool col = true;
                for (int k = 0; k < n; k++) {
                    col &= mat[k][j] <= h;
                }

                if (!(row || col)) return false;
            }
        }
    }

    return true;
}

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> mat[i][j];
            }
        }

        cout << "Case #" << task << ": " << (check() ? "YES" : "NO") << endl;
    }

    return 0;
}
