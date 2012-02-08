#include <cstdio>
#include <vector>

using namespace std;

class GogoXBallsAndBinsEasy {
    private:

    public:
        int solve(vector <int> T)
        {
            int res = 0;
            for (int i = 0, j = T.size() - 1; i < j; i++, j--)
                res += T[j] - T[i];
            return res;
        }
};
