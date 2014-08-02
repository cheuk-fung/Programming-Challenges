#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    long long f[n + 1];
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        for (int l = 0; l < i; l++) {
            int r = i - 1 - l;
            f[i] += f[l] * f[r];
        }
    }

    cout << f[n] << " " << n + 1 << endl;

    return 0;
}
