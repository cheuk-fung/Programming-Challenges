#include <iostream>

using namespace std;

int main()
{
    int n;
    while (cin >> n) {
        if (n == 3) cout << 5 << endl;
        else {
            for (int i = 1; ; i += 2) {
                if ((i * i + 1) >> 1 >= n) {
                    cout << i << endl;
                    break;
                }
            }
        }
    }

    return 0;
}

