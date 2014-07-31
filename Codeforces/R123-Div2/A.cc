#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    while (cin >> a >> b >> c) {
        cout << a * c / b + (a * c % b != 0) - c << endl;
    }

    return 0;
}

