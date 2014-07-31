#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    int x, y, z;
    cin >> x >> y >> z;
    int x1, y1, z1;
    cin >> x1 >> y1 >> z1;
    int a[6];
    for (int i = 0; i < 6; i++) cin >> a[i];

    int ans = 0;
    if (y < 0) ans += a[0];
    if (y > y1) ans += a[1];
    if (z < 0) ans += a[2];
    if (z > z1) ans += a[3];
    if (x < 0) ans += a[4];
    if (x > x1) ans += a[5];

    cout << ans << endl;

    return 0;
}

