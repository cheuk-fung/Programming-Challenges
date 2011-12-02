#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::min;

class DropCoins {
    private:
        int cnt[31][31];
        
        int sum(int x1, int y1, int x2, int y2)
        {
            int res = cnt[x2][y2];
            if (x1) res -= cnt[x1 - 1][y2];
            if (y1) res -= cnt[x2][y1 - 1];
            if (x1 && y1) res += cnt[x1 - 1][y1 - 1];
            return res;
        }
    public:
        int getMinimum(vector <string> board, int K)
        {
            const int INF = 0x3f3f3f3f;
            int res = INF,
                n = board.size(), m = board[0].length();

            cnt[0][0] = (board[0][0] == 'o');
            for (int i = 1; i < n; i++)
                cnt[i][0] = cnt[i - 1][0] + (board[i][0] == 'o');
            for (int j = 1; j < m; j++)
                cnt[0][j] = cnt[0][j - 1] + (board[0][j] == 'o');
            for (int i = 1; i < n; i++)
                for (int j = 1; j < m; j++)
                    cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - \
                                cnt[i - 1][j - 1] + (board[i][j] == 'o');

            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    for (int k = i; k < n; k++)
                        for (int l = j; l < m; l++)
                            if (sum(i, j, k, l) == K) {
                                int now = 0;
                                now += min(i * 2 + n - k - 1, i + (n - k - 1) * 2);
                                now += min(j * 2 + m - l - 1, j + (m - l - 1) * 2);
                                res = min(res, now);
                            }

            return res == INF ? -1 : res;
        }
};

int main()
{
    vector<string> vs;
    vs.push_back(".o..");
    vs.push_back("oooo");
    vs.push_back("..o.");
    DropCoins dc;
    printf("%d\n", dc.getMinimum(vs, 3));

    return 0;
}
