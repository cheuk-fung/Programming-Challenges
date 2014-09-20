#include <algorithm>
#include <string>
#include <vector>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class UndoHistory {
    private:
        int lcp(string s, string t)
        {
            int r = 0;
            int minlength = min(SIZE(s), SIZE(t));
            for (r = 0; r < minlength; r++) {
                if (s[r] != t[r]) {
                    break;
                }
            }
            return r;
        }

    public:
        int minPresses(vector <string> lines)
        {
            int sum = SIZE(lines[0]) + 1;
            for (int i = 1; i < SIZE(lines); i++) {
                int prefix = 0;
                for (int j = 0; j < i; j++) {
                    prefix = max(prefix, lcp(lines[i], lines[j]));
                }
                int eps = 2 + SIZE(lines[i]) - prefix;
                if (lcp(lines[i], lines[i - 1]) == SIZE(lines[i - 1])) {
                    eps = min(eps, SIZE(lines[i]) - SIZE(lines[i - 1]));
                }
                sum += eps + 1;
            }

            return sum;
        }
};
