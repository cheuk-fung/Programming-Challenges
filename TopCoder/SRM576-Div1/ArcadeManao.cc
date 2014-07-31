#include <string>
#include <vector>
#include <cstring>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class ArcadeManao {
    private:
        vector<string> level;
        int n, m;
        int tx, ty;
        bool mat[100][100];

        bool check(int x, int y, int l)
        {
            if (x == tx && y == ty) return true;
            if (level[x][y] == '.' || mat[x][y]) return false;
            mat[x][y] = true;

            if (y > 0 && check(x, y - 1, l)) return true;
            if (y + 1 < m && check(x, y + 1, l)) return true;
            for (int i = 1; i <= l; i++) {
                if (x - i >= 0 && check(x - i, y, l)) return true;
                if (x + i < n && check(x + i, y, l)) return true;
            }

            return false;
        }

    public:
        int shortestLadder(vector <string> level, int coinRow, int coinColumn)
        {
            this->level = level;
            n = (int)level.size();
            m = (int)level[0].length();
            tx = coinRow - 1;
            ty = coinColumn - 1;

            int l = 0, r = n;
            while (l < r) {
                memset(mat, 0, sizeof mat);
                int mid = (l + r - 1) >> 1;
                if (check(n - 1, 0, mid)) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }

            return l;

        }
};
