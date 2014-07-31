#include <cmath>
#include <iostream>

using namespace std;

const double eps = 1e-8;

int main()
{
    long long k, b, n, t;
    cin >> k >> b >> n >> t;
    if (k == 1) {
        cout << max(0, (int)ceil((1.0 + n * b - t) / b - eps)) << endl;
    } else {
        cout << max(0, (int)ceil(n - log((t * (k - 1.0) + b) / (k - 1.0 + b)) / log(k) - eps)) << endl;
    }

    return 0;
}

