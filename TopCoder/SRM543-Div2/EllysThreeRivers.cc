#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const double DINF = 1.0/0.0f;
const double eps = 1e-12;

inline bool ls(double x, double y) { return x + eps < y; }
inline double fmin(double x, double y) { return ls(x, y) ? x : y; }

template<class T> inline T sqr(T x) { return x * x; }

class EllysThreeRivers {
    private:
        double calc(int idx, double rest, int walk, vector<int> &width, vector<int> &swim)
        {
            if (idx == 3) {
                return rest / walk;
            }

            double res = DINF;
            double l = 0;
            double r = rest;
            while (ls(l, r)) {
                double p1 = (l + r) / 2.0;
                double p2 = (p1 + r) / 2.0;
                double ans1 = sqrt(sqr(width[idx]) + sqr(p1)) / swim[idx] + calc(idx + 1, rest - p1, walk, width, swim);
                double ans2 = sqrt(sqr(width[idx]) + sqr(p2)) / swim[idx] + calc(idx + 1, rest - p2, walk, width, swim);
                if (ls(ans1, ans2)) {
                    r = p2;
                } else {
                    l = p1;
                }
                res = fmin(res, fmin(ans1, ans2));
            }

            return res;
        }

    public:
        double getMin(int length, int walk, vector <int> width, vector <int> swim)
        {
            return calc(0, length, walk, width, swim);
        }
};
