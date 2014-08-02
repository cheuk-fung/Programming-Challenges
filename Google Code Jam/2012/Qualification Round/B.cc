#include <iostream>

using namespace std;

int tot_score[110];

int main()
{
    int tasks;
    cin >> tasks;
    for (int task = 1; task <= tasks; task++) {
        int n, s, p;
        cin >> n >> s >> p;
        for (int i = 0; i < n; i++) {
            cin >> tot_score[i];
        }

        int cnt = 0, surprising = 0;
        for (int i = 0; i < n; i++) {
            if ((tot_score[i] + 2) / 3 >= p) {
                cnt++;
            } else {
                int a = p, b = (tot_score[i] - a) / 2, c = tot_score[i] - a - b;
                if (b < 0 || c < 0 || a - b > 2 || a - c > 2) continue;
                if (a - b == 2 || a - c == 2) {
                    if (surprising < s) {
                        cnt++;
                        surprising++;
                    }
                } else {
                    cnt++;
                }
            }
        }

        cout << "Case #" << task << ": " << cnt << endl;
    }

    return 0;
}
