#include <iostream>
#include <algorithm>

using namespace std;

struct Team {
    int prob, pt;

    bool operator<(const Team &o) const
    {
        if (prob == o.prob) return pt < o.pt;
        return prob > o.prob;
    }

    bool operator==(const Team &o) const
    {
        return prob == o.prob && pt == o.pt;
    }
};
Team teams[100];

int main()
{
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) {
            cin >> teams[i].prob >> teams[i].pt;
        }
        sort(teams, teams + n);

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (teams[i] == teams[k - 1]) {
                cnt++;
            }
        }

        cout << cnt << endl;
    }

    return 0;
}

