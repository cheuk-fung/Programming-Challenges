#include <iostream>

using namespace std;

int n;
int days[1010];

bool check(int d)
{
    if (days[0] < d || days[n - 1] < d) return false;
    for (int i = 1; i < n - 1; i++) {
        if (days[i] < d && days[i + 1] < d) return false;
    }
    return true;
}

int main()
{
    while (cin >> n) {
        int max_day = 0;
        for (int i = 0; i < n; i++) {
            cin >> days[i];
            max_day = max(max_day, days[i]);
        }

        int l = 0, r = max_day;
        for (int mid = (l + r) >> 1; l < r; mid = (l + r + 1) >> 1) {
            if (check(mid)) l = mid;
            else r = mid - 1;
        }

        cout << l << endl;
    }

    return 0;
}

