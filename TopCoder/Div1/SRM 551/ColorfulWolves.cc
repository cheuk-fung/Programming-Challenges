#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
template<class T> inline int SIZE(const T &x) { return x.size(); }

class ColorfulWolves {
    private:
        int mat[100][100];

    public:
        int getmin(vector <string> colormap)
        {
            memset(mat, 0x3f, sizeof mat);
            int n = SIZE(colormap);
            for (int i = 0; i < n; i++) {
                mat[i][i] = 0;
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    if (colormap[i][j] == 'Y') {
                        mat[i][j] = cnt++;
                    }
                }
            }

            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                    }
                }
            }

            return mat[0][n - 1] == INF ? -1 : mat[0][n - 1];
        }
};
