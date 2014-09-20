#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cnt += (a + b + c) >= 2;
    }
    cout << cnt << endl;

    return 0;
}

