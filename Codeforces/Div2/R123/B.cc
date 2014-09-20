#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    while (cin >> n >> m) {
        vector<int> seq;
        if (m & 1) {
            int mid = (m + 1) / 2;
            seq.push_back(mid);
            for (int i = 1; i < mid; i++) {
                seq.push_back(mid - i);
                seq.push_back(mid + i);
            }
        } else {
            int l = (m + 1) / 2;
            int r = l + 1;
            for (int i = 0; i < l; i++) {
                seq.push_back(l - i);
                seq.push_back(r + i);
            }
        }

        for (int i = 0; i < n; i++) {
            cout << seq[i % seq.size()] << endl;
        }
    }

    return 0;
}

