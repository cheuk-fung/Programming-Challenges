#include <cstdio>
#include <iostream>

using namespace std;

const int INF = 0x3f3f3f3f;

long long go(long long dx, long long x, long long n)
{
    if (dx > 0) return (n - x) / dx;
    if (dx < 0) return (x - 1) / -dx;
    return INF;
}

int main()
{
    long long n, m;
    long long x, y;
    int k;

    cin >> n >> m;
    cin >> x >> y;
    cin >> k;

    long long steps = 0;
    for (int i = 0; i < k; i++) {
        long long dx, dy;
        cin >> dx >> dy;

        long long ds = min(go(dx, x, n), go(dy, y, m));
        steps += ds;
        x += dx * ds;
        y += dy * ds;
    }

    cout << steps << endl;

    return 0;
}

