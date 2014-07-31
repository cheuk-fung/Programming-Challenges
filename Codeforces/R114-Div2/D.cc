#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, double> pii;

int n, l, k;
double f[222][222][222];

vector<pii> tours;

double dp(int x, int cnt, int size)
{
    size = min(size, 200);

    double res = 0.0;
    if (x == n) {
        if (cnt >= l) {
            res = 1.0;
        }
        return f[x][cnt][size] = res;
    }

    if (f[x][cnt][size] != -1) {
        return f[x][cnt][size];
    }

    res = (1.0 - tours[x].second) * dp(x + 1, cnt, size);
    if (size + tours[x].first >= 0) {
        res += tours[x].second * dp(x + 1, cnt + 1, size + tours[x].first);
    }

    return f[x][cnt][size] = res;
}

int main()
{
    while (cin >> n >> l >> k) {
        tours.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= 200; k++) {
                    f[i][j][k] = -1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            double tp;
            cin >> tp;
            tours.push_back(pii(0, tp / 100));
        }
        for (int i = 0; i < n; i++) {
            cin >> tours[i].first;
        }

        sort(tours.begin(), tours.end(), greater<pii>());

        printf("%.10lf\n", dp(0, 0, k));
    }


    return 0;
}

