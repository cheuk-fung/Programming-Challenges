#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class DengklekMakingChains {
    private:

    public:
        int maxBeauty(vector <string> chains)
        {
            int one = 0, clean = 0;
            int left[chains.size()], right[chains.size()];
            memset(left, 0, sizeof(left));
            memset(right, 0, sizeof(right));
            for (int i = 0; i < chains.size(); i++) {
                if (chains[i].find('.') == string::npos)
                    clean += chains[i][0] - '0' +                           \
                             chains[i][1] - '0' +                           \
                             chains[i][2] - '0';
                else {
                    int t = 0;
                    if (chains[i][1] != '.') {
                        t = chains[i][1] - '0';
                        one = max(one, t);
                    }
                    if (chains[i][0] != '.') {
                        int l = t + chains[i][0] - '0';
                        left[i] = l;
                        one = max(one, l);
                    }
                    if (chains[i][2] != '.') {
                        int r = t + chains[i][2] - '0';
                        right[i] = r;
                        one = max(one, r);
                    }
                }
            }

            int side = 0;
            for (int i = 0; i < chains.size(); i++)
                for (int j = 0; j < chains.size(); j++)
                    if (i != j) side = max(side, left[i] + right[j]);

            return max(one, clean + side);
        }
};
