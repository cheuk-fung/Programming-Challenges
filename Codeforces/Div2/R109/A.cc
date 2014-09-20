#include <iostream>

using namespace std;

int main()
{
    int n, best, worst;
    cin >> n;
    cin >> best;
    worst = best;

    int cnt = 0;
    for (int i = 1; i < n; i++) {
        int t;
        cin >> t;
        if (t > best) {
            cnt++;
            best = t;
        }
        if (t < worst) {
            cnt++;
            worst = t;
        }
    }

    cout << cnt << endl;

    return 0;
}

