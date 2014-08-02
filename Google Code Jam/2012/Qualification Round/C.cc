#include <iostream>
#include <cstring>

using namespace std;

int pow10[10];
int check[2000010];

int main()
{
    pow10[0] = 1;
    for (int i = 1; i < 10; i++) {
        pow10[i] = pow10[i - 1] * 10;
    }

    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        memset(check, 0xff, sizeof(check));

        int A, B;
        cin >> A >> B;

        int digits = 0;
        for (int i = A; i; digits++, i /= 10) ;

        int cnt = 0;
        for (int n = A; n < B; n++) {
            for (int i = 1; i < digits; i++) {
                int m = n % pow10[i] * pow10[digits - i] + n / pow10[i];
                if (n < m && m <= B) {
                    if (check[m] != n) {
                        cnt++;
                        check[m] = n;
                    }
                }
            }
        }

        cout << "Case #" << task << ": " << cnt << endl;
    }

    return 0;
}
