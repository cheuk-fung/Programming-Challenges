#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int mat[1000][1000];

class DrawingPointsDivOne {
    private:
        bool check(int cnt, const vector<int> &x, const vector<int> &y) {
            memset(mat, 0, sizeof mat);
            int n = x.size();
            int xmn = INF, xmx = -INF, ymn = INF, ymx = -INF;
            for (int i = 0; i < n; i++) {
                int xx = x[i], yy = y[i];
                for (int j = xx * 2 - cnt; j <= xx * 2 + cnt; j += 2) {
                    for (int k = yy * 2 - cnt; k <= yy * 2 + cnt; k += 2) {
                        mat[j + 500][k + 500] = 1;
                        xmn = min(xmn, j + 500);
                        xmx = max(xmx, j + 500);
                        ymn = min(ymn, k + 500);
                        ymx = max(ymx, k + 500);
                    }
                }
            }
            int round = 1;
            while (true) {
                bool none = true;
                for (int i = xmn; i <= xmx; i++) {
                    for (int j = ymn; j <= ymx; j++) {
                        if (mat[i][j] == round && mat[i][j + 2] == round && mat[i + 2][j] == round && mat[i + 2][j + 2] == round) {
                            mat[i + 1][j + 1] = round + 1;
                            none = false;
                        }
                    }
                }
                if (none) break;
                round++;
                if (round - 1 == cnt) break;
            }

            int num = 0;
            for (int i = xmn; i <= xmx; i++) {
                for (int j = ymn; j <= ymx; j++) {
                    if (mat[i][j] == round) {
                        num++;
                    }
                }
            }

            return num == n;
        }

    public:
        int maxSteps(vector <int> x, vector <int> y) {
            int mx = 200;
            int l = 0, r = mx;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (check(mid, x, y)) l = mid;
                else r = mid - 1;
            }
            if (l == mx) return -1;
            return l;
        }
};
