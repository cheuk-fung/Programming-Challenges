#include <cstring>
#include <string>

using namespace std;

int f[1 << 21];
class EllysCheckers {
    private:
        int toInt(string s)
        {
            int res = 0;
            for (int i = 0; i < s.length(); i++)
                res = res * 2 + (s[i] == 'o');
            return res;
        }

        bool dp(string s)
        {
            s[s.length() - 1] = '.';
            int idx = toInt(s);
            if (f[idx] != -1) return f[idx];

            for (int i = 0; i < s.length(); i++) {
                if (s[i] == 'o') {
                    if (i + 1 < s.length() && s[i + 1] =='.') {
                        string t = s;
                        t[i] = '.';
                        t[i + 1] = 'o';
                        if (!dp(t)) return f[idx] = 1;
                    }
                    if (i + 3 < s.length() && s[i + 1] == 'o' && s[i + 2] == 'o' && s[i + 3] == '.') {
                        string t = s;
                        t[i] = '.';
                        t[i + 3] = 'o';
                        if (!dp(t)) return f[idx] = 1;
                    }
                }
            }

            return f[idx] = 0;
        }

    public:
        string getWinner(string board)
        {
            memset(f, 0xff, sizeof(f));
            f[0] = 0;
            return dp(board) ? "YES" : "NO";
        }
};
