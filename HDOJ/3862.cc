/*
 *  SRC: HDOJ 3862
 * PROB: The Lost Traveler
 * ALGO: NULL
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool check(const vector<double> &degree)
{
    for (int i = 1; i < degree.size(); i++) {
        if (degree[i] - degree[i - 1] > 180) {
            return false;
        }
    }
    return true;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        vector<double> degree;
        degree.push_back(0);
        for (int i = 1; i <= n; i++) {
            double d;
            scanf("%lf", &d);
            d += degree.back() + 360;
            while (d >= 360) d -= 360;
            degree.push_back(d);
        }
        degree.push_back(360);
        sort(degree.begin(), degree.end());
        puts(check(degree) ? "Yes" : "No");
    }

    return 0;
}

