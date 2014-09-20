#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int n, m;
bool mat[1010][1010];
vector<pii> moves;

bool check_point(int x, int y)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!mat[x + i][y + j]) return false;
    return true;
}

bool check(int mid)
{
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < mid; i++) {
        mat[moves[i].first][moves[i].second] = true;
    }

    for (int i = 0; i <= n - 3; i++) {
        for (int j = 0; j <= n - 3; j++) {
            if (check_point(i, j)) return true;
        }
    }

    return false;
}

int main()
{
    while (cin >> n >> m) {
        moves.clear();
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            moves.push_back(pii(x - 1, y - 1));
        }
        if (!check(m)) {
            cout << -1 << endl;
            continue;
        }

        int l = 0, r = m;
        while (l < r) {
            int mid = (l + r - 1) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        cout << l << endl;
    }

    return 0;
}

