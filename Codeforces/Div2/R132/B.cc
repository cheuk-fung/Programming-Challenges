#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 5010;

int r1[MAXN], p1[MAXN], p2[MAXN];

int main(int argc, char *argv[])
{
    int n, m, k, A, B;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> r1[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> p1[i];
    cin >> k;
    for (int i = 0; i < k; i++) cin >> p2[i];
    cin >> A >> B;

    double r2 = 0.0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            double t = sqrt(1.0 * p1[i] * B / (p1[i] * B + p2[j] * A));
            r2 = max(r2, t);
        }
    }
    r2 *= *max_element(r1, r1 + n);
    cout.precision(13);
    cout << r2 << endl;

    return 0;
}
