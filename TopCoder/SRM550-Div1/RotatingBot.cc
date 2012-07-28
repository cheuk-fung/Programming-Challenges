#include <vector>
#include <cstring>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

int dir[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

class RotatingBot {
    private:
        bool mat[200][200];
        bool check(const vector<int> &moves, int w, int h)
        {
            memset(mat, 0, sizeof mat);
            for (int i = 0; i <= w; i++) mat[i][0] = mat[i][h + 1] = true;
            for (int i = 0; i <= h; i++) mat[0][i] = mat[w + 1][i] = true;
            int x = w - moves[0];
            int y = h - moves[1];
            if (x <= 0 || y <= 0) return false;

            mat[x][y] = true;
            int d = 0;
            for (int i = 0; i < SIZE(moves); i++) {
                for (int j = 0; j < moves[i]; j++) {
                    x += dir[d][0];
                    y += dir[d][1];
                    if (mat[x][y] || !(0 < x && x <= w) || !(0 < y && y <= h)) return false;
                    mat[x][y] = true;
                }
                int xx = x + dir[d][0];
                int yy = y + dir[d][1];
                if (i + 1 < SIZE(moves) && !mat[xx][yy]) return false;
                d = (d + 1) % 4;
            }

            return true;
        }

    public:
        int minArea(vector <int> moves)
        {
            if (SIZE(moves) == 1) return moves[0] + 1;
            if (SIZE(moves) == 2) return (moves[0] + 1) * (moves[1] + 1);
            if (SIZE(moves) == 3) return (max(moves[0], moves[2]) + 1) * (moves[1] + 1);

            int w = moves[2] + 1;
            int h = max(moves[1], moves[3]) + 1;
            if (check(moves, w, h)) return w * h;
            return -1;
        }
};
