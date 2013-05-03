#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MOD = 1000000007;
template<class T> inline int SIZE(const T &x) { return x.size(); }

class GooseInZooDivOne {
    private:
        vector<string> field;
        int dist;
        int n, m;
        bool vis[100][100];

        int floodfill(int x, int y)
        {
            vis[x][y] = true;
            int res = 1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (abs(i - x) + abs(j - y) <= dist && field[i][j] == 'v' && !vis[i][j]) {
                        res += floodfill(i, j);
                    }
                }
            }
            return res;
        }

        long long exp2(int x)
        {
            long long res = 1;
            for (int i = 0; i < x; i++) res = (res << 1) % MOD;
            return res;
        }

    public:
        int count(vector <string> field, int dist)
        {
            this->field = field;
            this->dist = dist;
            n = SIZE(field);
            m = SIZE(field[0]);
            memset(vis, 0, sizeof vis);

            int odd = 0, even = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (field[i][j] == 'v' && !vis[i][j]) {
                        int cnt = floodfill(i, j);
                        if (cnt & 1) odd++;
                        else even++;
                    }
                }
            }

            long long res = exp2(even) * exp2(odd - 1) % MOD;
            res--;
            if (res < 0) res += MOD;

            return res;
        }
};
