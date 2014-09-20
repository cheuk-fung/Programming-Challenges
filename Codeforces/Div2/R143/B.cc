#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

vector<int> run(int n, int d, int l)
{
    vector<int> res;
    int x = abs(d) / (n / 2);
    int b = 1, a = b + x;
    if (a + (abs(d) % (n / 2) != 0) > l) {
        res.push_back(-1);
        return res;
    }

    int cnt = 0;
    a++;
    if (d < 0) swap(a, b);
    for (int i = 0; i < abs(d) % (n / 2); i++, cnt++) {
        res.push_back(a);
        res.push_back(b);
    }
    if (d < 0) swap(a, b);
    a--;
    if (d < 0) swap(a, b);
    for ( ; cnt < n / 2; cnt++) {
        res.push_back(a);
        res.push_back(b);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int n, d, l;
    while (cin >> n >> d >> l) {
        if (n & 1) {
            bool ok = false;
            for (int i = 1; i <= l; i++) {
                vector<int> r = run(n - 1, i - d, l);
                if (r[0] != -1) {
                    cout << i << " ";
                    for (int i = 0; i < SIZE(r); i++) cout << r[i] << " ";
                    cout << endl;
                    ok = true;
                    break;
                }
            }
            if (!ok) cout << -1 << endl;
        } else {
            vector<int> r = run(n, d, l);
            if (r[0] == -1) {
                cout << -1 << endl;
            } else {
                for (int i = 0; i < SIZE(r); i++) cout << r[i] << " ";
                cout << endl;
            }
        }
    }

    return 0;
}

