#include <vector>
#include <map>

using namespace std;

typedef vector<int>::const_iterator vci;

class ContestWinner {
    private:

    public:
        int getWinner(vector <int> events)
        {
            int max_cnt = 0;
            int res;
            map<int, int> cnt;
            for (vci it = events.begin(); it != events.end(); it++) {
                cnt[*it]++;
                if (cnt[*it] > max_cnt) {
                    max_cnt = cnt[*it];
                    res = *it;
                }
            }
            return res;
        }
};

