#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, t;
    string que;
    cin >> n >> t >> que;

    for (int i = 0; i < t; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (que[j] == 'B' && que[j + 1] == 'G') {
                swap(que[j], que[j + 1]);
                j++;
            }
        }
    }

    cout << que << endl;


    return 0;
}
