#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <climits>

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

int main()
{
    int T;
    scanf("%d", &T);

    for (int task = 1; task <= T; task++) {
        printf("Case #%d: ", task);

        long long OB;
        int N;
        scanf("%lld%d", &OB, &N);

        long long OX[38];
        fill(OX, OX + 37, 0);
        for (int i = 0; i < N; i++) {
            scanf("%lld", OX + i);
        }
        sort(OX, OX + 37);
        OX[37] = LLONG_MAX;

        double ans = 0;
        for (int i = 0; i < 37; i++) {
            long long X[38];
            for (int j = 0; j < 38; j++) X[j] = OX[j];
            long long B = OB;
            for (int pi = i + 1; X[pi] == X[i]; pi++) {
                X[pi]++;
                B--;
            }
            if (B < 0) break;

            long long sum = 0;
            for (int j = 0; j <= i; j++) sum += X[j];
            int cnt = i + 1;
            long long amount = X[i];
            long long res = B - amount * cnt + sum;
            if (res < 0) break;
            int div = cnt;
            while (true) {
                double now = 0;
                for (int j = 0; j < cnt; j++) {
                    now += (amount - X[j]) * 36.0 / cnt;
                }
                ans = max(ans, now - (OB - res));

                long long addition = res / div;
                if (addition == 0) break;
                if (amount + addition >= X[div]) {
                    res -= (X[div] - 1 - amount) * div;
                    assert(res >= 0);
                    amount = X[div] - 1;
                    int pdiv = div;
                    while (X[div] == X[pdiv]) div++;
                } else {
                    amount += addition;
                    res -= addition * div;
                }
            }
        }
        printf("%.10f\n", ans);
    }

    return 0;
}
