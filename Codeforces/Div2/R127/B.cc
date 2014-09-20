#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, x;

void calc_x(vector<int> *pos, vector<int> &choose, int p)
{
    if (p == n) {
        int tx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (choose[i] > choose[j]) tx++;
            }
        }
        x = min(x, tx);
    } else {
        for (int i = 0; i < pos[p].size(); i++) {
            choose[p] = pos[p][i];
            calc_x(pos, choose, p + 1);
        }
    }
}

int similarity(const vector<string> &lesha, const vector<string> &a)
{
    vector<int> pos[n];
    for (int i = 0; i < lesha.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (lesha[i] == a[j]) {
                pos[i].push_back(j);
            }
        }
        if (pos[i].empty()) return -1;
    }

    x = INF;
    vector<int> choose(n);
    calc_x(pos, choose, 0);

    return n * (n - 1) / 2 - x + 1;
}

int main()
{
    while (cin >> n) {
        vector<string> lesha;
        for (int i = 0; i < n; i++) {
            string t;
            cin >> t;
            lesha.push_back(t);
        }

        int m;
        cin >> m;
        vector<string> archive[m];
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            while (k--) {
                string t;
                cin >> t;
                archive[i].push_back(t);
            }
        }

        int p = -1;
        int idx = -1;
        for (int i = 0; i < m; i++) {
            int tp = similarity(lesha, archive[i]);
            if (tp > p) {
                p = tp;
                idx = i + 1;
            }
        }

        if (p == -1) cout << "Brand new problem!" << endl;
        else {
            cout << idx << endl;
            cout << "[:";
            while (p--) cout << '|';
            cout << ":]" << endl;
        }
    }

    return 0;
}

