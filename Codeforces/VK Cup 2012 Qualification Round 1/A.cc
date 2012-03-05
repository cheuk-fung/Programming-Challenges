#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    int score_k;
    for (int i = 0; i < k; i++) {
        cin >> score_k;
        if (score_k) cnt++;
    }
    for (int i = k; i < n; i++) {
        int score;
        cin >> score;
        if (score_k && score == score_k) cnt++;
    }
    cout << cnt << endl;

    return 0;
}

