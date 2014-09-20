#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    int cnt = 0;
    for (int i = a, j = b, k = c; i && j && k; i--, j--, k--) {
        if (i == 1) cnt += j * k;
        else if (j == 1) cnt += i * k;
        else if (k == 1) cnt += i * j;
        else cnt += (i + j + k) * 2 - 6;
    }
    cout << cnt << endl;

    return 0;
}

