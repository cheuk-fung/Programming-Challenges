#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;

int run(int n, int a, int b)
{
    int cnt = 0;
    int mistake = 0;
    char last = 0;
    while (true) {
        if (b == 1) {
            int k = a - 1;
            mistake += k + (last == 'T');
            cnt += k + 1;
            if (cnt == n) break;
            else return INF;
        } else if (a == 1) {
            int k = b - 1;
            mistake += k - 1 + (last == 'B');
            cnt += k + 1;
            if (cnt == n) break;
            else return INF;
        }
        if (a == 0 || b == 0) return INF;

        if (a > b) {
            int k = a / b;
            cnt += k;
            mistake += k - 1 + (last == 'T');
            last = 'T';
            a -= k * b;
        } else {
            int k = b / a;
            cnt += k;
            mistake += k - 1 + (last == 'B');
            last = 'B';
            b -= k * a;
        }
    }

    return mistake;
}

string get(int n, int a, int b)
{
    string seq;
    while (a != b) {
        if (a > b) {
            a -= b;
            seq += "T";
        } else {
            b -= a;
            seq += "B";
        }
    }
    seq += "T";
    reverse(seq.begin(), seq.end());

    return seq;
}

int main()
{
    int n, r;
    cin >> n >> r;

    int min_mistake = INF;
    int min_a, min_b;
    for (int i = 1; i <= r; i++) {
        int ret = run(n, i, r);
        if (ret < min_mistake) {
            min_mistake = ret;
            min_a = i;
            min_b = r;
        }

        ret = run(n, r, i);
        if (ret < min_mistake) {
            min_mistake = ret;
            min_a = r;
            min_b = i;
        }
    }

    if (min_mistake == INF) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << min_mistake << endl;
        cout << get(n, min_a, min_b) << endl;
    }

    return 0;
}

