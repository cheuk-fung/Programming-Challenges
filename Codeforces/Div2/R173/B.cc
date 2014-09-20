#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

char color[1000010];

int main()
{
    int n;
    cin >> n;
    int A = 0, G = 0;
    for (int i = 0; i < n; i++) {
        int a, g;
        cin >> a >> g;
        int TA = A - G + a;
        int TG = A - G - g;
        if (abs(TA) > 500 && abs(TG) > 500) {
            cout << -1 << endl;
            return 0;
        }
        if (abs(TA) < abs(TG)) {
            A += a;
            color[i] = 'A';
        } else {
            G += g;
            color[i] = 'G';
        }
    }
    color[n] = '\0';
    cout << color << endl;

    return 0;
}
