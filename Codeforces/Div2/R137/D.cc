#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int MAXN = 1e5 + 10;

class Disjoint_set {
    public:
        int a[MAXN];

        void build() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

int n, x;
int a[MAXN], b[MAXN];

int work(int *a, int *b)
{
    sort(a, a + n);
    sort(b, b + n);
    int res = 0;
    ds.build();
    for (int i = 0; i < n; i++) {
        if (a[i] + b[n - 1] < x) continue;
        int r = lower_bound(b, b + n, x - a[i]) - b;
        if (ds.find(r) < n) {
            res++;
            r = ds.find(r);
            ds.join(r + 1, r);
        }
    }
    return res;
}

int main()
{
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int r = work(a, b);
    cout << 1 << " " << r << endl;

    return 0;
}
