#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <ctime>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> pii;

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        int E, R, N;
        cin >> E >> R >> N;
        vector<int> v;
        for (int i = 0; i < N; i++) {
            int a;
            cin >> a;
            v.push_back(a);
        }

        int ans = 0;
        int f[N + 10][E + 10];
        memset(f, 0, sizeof f);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= E; j++) {
                for (int k = 0; k <= j; k++) {
                    int next = min(j - k + R, E);
                    f[i + 1][next] = max(f[i + 1][next], f[i][j] + k * v[i]);
                    ans = max(ans, f[i + 1][next]);
                }
            }
        }

        cout << "Case #" << task << ": " << ans << endl;
    }

    return 0;
}
