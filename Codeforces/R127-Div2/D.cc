#include <iostream>

using namespace std;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
template<class T> inline T sqr(T x) { return x * x; }

long long mat[1010][1010];
long long row[1010], col[1010];
long long sumx[1010], sumy[1010];

int main()
{
    int n, m;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            row[i] += mat[i][j];
            col[j] += mat[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sumx[i] += row[j] * sqr((j - i) * 4 + 2);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            sumy[i] += col[j] * sqr((j - i) * 4 + 2);
        }
    }

    long long ans = LLINF;
    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (sumx[i] + sumy[j] < ans) {
                ans = sumx[i] + sumy[j];
                x = i;
                y = j;
            }
        }
    }
    cout << ans << endl;
    cout << x << " " << y << endl;

    return 0;
}

