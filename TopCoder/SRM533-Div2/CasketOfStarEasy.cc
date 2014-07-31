#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class CasketOfStarEasy {
    private:
        vector<int> order;
        bool vis[10];

    public:
        int maxEnergy(vector <int> weight)
        {
            for (int i = 1; i < weight.size() - 1; i++) order.push_back(i);

            int res = 0;
            do {
                int tot = 0;
                memset(vis, false, sizeof(vis));
                for (int i = 0; i < order.size(); i++) {
                    int l = order[i], r = order[i];
                    vis[order[i]] = true;
                    while (vis[l]) l--;
                    while (vis[r]) r++;
                    tot += weight[l] * weight[r];
                }
                res = max(res, tot);
            } while (next_permutation(order.begin(), order.end()));

            return res;
        }
};
