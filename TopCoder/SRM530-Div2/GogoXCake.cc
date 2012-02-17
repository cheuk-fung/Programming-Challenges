#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class GogoXCake {
    private:
        typedef pair<int, int> position;

        position tlDot(const vector<string> &map)
        {
            for (int i = 0; i < map.size(); i++)
                for (int j = 0; j < map[i].length(); j++)
                    if (map[i][j] == '.') return position(i, j);
            return position(-1, -1);
        }

    public:
        string solve(vector <string> cake, vector <string> cutter)
        {
            int caH = cake.size(),
                caW = cake[0].length(),
                cuH = cutter.size(),
                cuW = cutter[0].length();
            position pos = tlDot(cutter);
            while (true) {
                position tPos = tlDot(cake);
                if (tPos == position(-1, -1)) return "YES";
                if (tPos.first + cuH - 1 >= caH) return "NO";
                if (tPos.second < pos.second) return "NO";
                if (tPos.second + cuW - pos.second - 1 >= caW) return "NO";

                int x = tPos.first,
                    y = tPos.second - pos.second;
                for (int i = 0; i < cuH; i++)
                    for (int j = 0; j < cuW; j++) {
                        if (cutter[i][j] == 'X') continue;
                        if (cake[x + i][y + j] != cutter[i][j]) return "NO";
                        cake[x + i][y + j] = 'X';
                    }
            }
        }
};
