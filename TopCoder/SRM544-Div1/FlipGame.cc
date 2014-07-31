#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class FlipGame {
    private:

    public:
        int minOperations(vector <string> board)
        {
            int cnt = 0;
            int pos[50];
            while (true) {
                memset(pos, 0xff, sizeof(pos));
                for (int i = 0; i < board.size(); i++) {
                    for (int j = board[i].length() - 1; j >= 0; j--) {
                        if (board[i][j] == '1') {
                            pos[i] = j;
                            break;
                        }
                    }
                }
                if (count(pos, pos + board.size(), -1) == board.size()) break;
                for (int i = 0, r = -1; i < board.size(); i++) {
                    r = max(r, pos[i]);
                    for (int j = 0; j <= r; j++) {
                        board[i][j] ^= 1;
                    }
                }
                cnt++;
            }
            return cnt;
        }
};

