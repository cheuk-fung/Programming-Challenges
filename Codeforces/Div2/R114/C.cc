#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

template<class T> inline T sqr(T x) { return x * x; }

int n, a, d;
vector<pii> buses;
vector<double> ans;

double arrive_time(int x)
{
    double t = buses[x].first;
    double v = buses[x].second;
    double time = (double)v / a;
    double distance = 0.5 * a * sqr(time);
    if (distance < d) {
        time += (d - distance) / v;
    } else {
        time = sqrt(d * 2.0 / a);
    }

    return time + t;
}

int main()
{
    while (cin >> n >> a >> d) {
        buses.clear();
        ans.clear();

        for (int i = 0; i < n; i++) {
            int t, v;
            cin >> t >> v;
            buses.push_back(pii(t, v));
        }

        ans.push_back(arrive_time(0));
        for (int i = 1; i < n; i++) {
            double arrive_time_tmp = arrive_time(i);
            if (arrive_time_tmp < ans[i - 1]) {
                ans.push_back(ans[i - 1]);
            } else {
                ans.push_back(arrive_time_tmp);
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%.10lf\n", ans[i]);
        }
    }

    return 0;
}

