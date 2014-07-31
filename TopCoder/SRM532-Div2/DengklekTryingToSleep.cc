#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class DengklekTryingToSleep {
    private:

    public:
        int minDucks(vector <int> ducks)
        {
            return *max_element(ducks.begin(), ducks.end()) -                \
                   *min_element(ducks.begin(), ducks.end()) + 1 -            \
                   ducks.size();
        }
};
