#include <iostream>

using namespace std;

int main()
{
    int x, t, a, b, da, db;
    while (cin >> x >> t >> a >> b >> da >> db) {
        bool ans = false;
        if (!x) ans = true;
        for (int i = 0; i < t; i++) {
            if (a - da * i == x) ans = true;
            if (b - db * i == x) ans = true;
        }
        for (int i = 0; i < t; i++)
            for (int j = 0; j < t; j++)
                if (a - da * i + b - db * j == x) ans = true;
        cout << (ans ? "YES" : "NO") << endl;
    }

    return 0;
}

