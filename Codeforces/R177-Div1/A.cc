#include <iostream>

using namespace std;

void work(int n, int k)
{
    if (n < k) {
        cout << -1 << endl;
        return ;
    }

    if (n == 1) {
        cout << 'a' << endl;
        return ;
    }

    if (k == 1) {
        cout << -1 << endl;
        return ;
    }

    cout << "ab";
    for (int i = 0; i < n - k; i++) {
        if (i & 1) cout << 'b';
        else cout << 'a';
    }
    char c = 'c';
    for (int i = n - k + 2; i < n; i++) {
        cout << c++;
    }
    cout << endl;
}

int main()
{
    int n, k;
    cin >> n >> k;
    work(n, k);

    return 0;
}
