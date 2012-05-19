#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const double DINF = 1.0/0.0f;
template<class T> inline T sqr(T x) { return x * x; }

double f[51][100001];

class EllysRivers {
    private:

    public:
        double getMin(int length, int walk, vector <int> width, vector <int> speed)
        {
            for (int i = 0 ; i <= width.size(); i++)
                for (int j = 0; j <= length; j++)
                    f[i][j] = DINF;

            f[0][0] = 0;
            for (int i = 0; i < width.size(); i++) {
                int k = 0;
                for (int j = 0; j <= length; j++) {
                    while (k < length && f[i][k + 1] + sqrt(sqr(width[i] * 1ll) + sqr(j - k - 1ll)) / speed[i] < f[i][k] + sqrt(sqr(width[i] * 1ll) + sqr(j - k * 1ll)) / speed[i]) k++;
                    f[i + 1][j] = f[i][k] + sqrt(sqr(width[i] * 1ll) + sqr(j - k * 1ll)) / speed[i];
                }
            }

            double res = DINF;
            for (int j = 0; j <= length; j++) {
                res = min(res, f[width.size()][j] + (length - j) * 1.0 / walk);
            }

            return res;
        }
};
