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

long long n, m;

const long long MOD = 1000002013;

long long calc(long long o, long long e, long long p)
{
    long long res = (e - o) * n % MOD - (e - o - 1) * (e - o) / 2 % MOD;
    while (res < 0) res += MOD;
    return res * p % MOD;
}

long long point[10000];
struct Passenger {
    long long o, e, p;
} pass[10000];;
long long cnt[10000];
long long station[10000];

int main()
{
    int T;
    cin >> T;

    for (int task = 1; task <= T; task++) {
        memset(cnt, 0, sizeof cnt);
        memset(station, 0, sizeof station);

        cin >> n >> m;

        long long money = 0;
        long long pcnt = 0;
        for (long long i = 0; i < m; i++) {
            long long o, e, p;
            cin >> o >> e >> p;
            money = (money + calc(o, e, p)) % MOD;
            pass[i].o = o;
            pass[i].e = e;
            pass[i].p = p;
            point[pcnt++] = o;
            point[pcnt++] = o + 1;
            point[pcnt++] = e;
        }
        sort(point, point + pcnt);
        pcnt = unique(point, point + pcnt) - point;
        for (long long i = 0; i < m; i++) {
            long long o, e, p;
            o = pass[i].o;
            e = pass[i].e;
            p = pass[i].p;
            long long l = lower_bound(point, point + pcnt, o) - point;
            long long r = lower_bound(point, point + pcnt, e) - point;
            assert(point[l] + 1 == point[l + 1]);
            for (long long j = l + 1; j <= r; j++) {
                station[j] += p;
            }
        }

        long long now = 0;
        while (true) {
            long long addition = 0;
            for (long long i = 0; i <= pcnt; i++) {
                if (station[i] == 0) continue;
                long long mn = station[i];
                long long j;
                for (j = i + 1; j <= pcnt && station[j]; j++) {
                    mn = min(mn, station[j]);
                }
                addition = calc(point[i] - 1, point[j - 1], mn);
                for (long long k = i; k < j; k++) {
                    station[k] -= mn;
                }
                break;
            }

            if (!addition) break;
            now = (now + addition) % MOD;
        }

        money -= now;
        while (money < 0) money += MOD;
        cout << "Case #" << task << ": " << money << endl;
    }

    return 0;
}
