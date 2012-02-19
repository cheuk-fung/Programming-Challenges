#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

class CasketOfStarEasy {
    private:
        int f[20][20];

    public:
        int maxEnergy(vector <int> weight)
        {
            memset(f, 0, sizeof(f));
            int n = weight.size();
            for (int l = 3; l <= n; l++) {
                for (int i = 0; i < n; i++) {
                    int j = i + l - 1;
                    if (j >= n) break;
                    for (int k = i + 1; k < j; k++)
                        f[i][j] = max(f[i][j], f[i][k] + f[k][j] + weight[i] * weight[j]);
                }
            }

            return f[0][n - 1];
        }
};
