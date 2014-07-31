#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class GogoXReimuHakurai {
    private:
        int row[51];

        int play(const vector<string> &choices, int x, int y)
        {
            if (x == choices.size() - 1) return 1;
            if (row[x] != -1) return row[x] != 0;

            int res = 0;
            for (int i = y + 1; i < choices[0].size(); i++)
                if (choices[x][i] == 'Y') res += play(choices, i, i);

            return row[x] = res;
        }

    public:
        int solve(vector <string> choices)
        {
            memset(row, 0xff, sizeof(row));

            return play(choices, 0, -1);
        }
};
