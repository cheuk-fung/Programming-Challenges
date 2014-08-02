#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <utility>
#include <algorithm>

using namespace std;

long long bestid[100], worseid[100];
long long best[100], worse[100];

int main()
{
    int T;
    cin >> T;

    for (int task = 1; task <= T; task++) {
        long long n;
        long long p;
        cin >> n >> p;

        long long x = 1ll << n;

        bestid[0] = worseid[0] = 0;
        bestid[n] = worseid[n] = x - 1;
        best[0] = worse[0] = 0;
        best[n] = worse[n] = x - 1;
        for (long long r = n - 1; r > 0; r--) {
            best[n - r] = (1ll << (n - r)) - 1;
            bestid[n - r] = bestid[n - r - 1] + (1ll << r);
        }
        for (long long r = 1; r < n; r++) {
            worse[r] = (1ll << n) - (1ll << (n - r));
            worseid[r] = worseid[r - 1] + (1ll << r);
        }

        p--;
        long long y = n, z = 0;
        while (worse[y] > p) y--;
        while (z < n && best[z + 1] <= p) z++;

        cout << "Case #" << task << ": " << worseid[y] << " " << bestid[z] << endl;
    }

    return 0;
}
