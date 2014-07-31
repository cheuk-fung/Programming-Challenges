#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class UnsortedSequence {
    private:

    public:
        vector<int> getUnsorted(vector<int> s)
        {
            sort(s.begin(), s.end());
            if (s[0] == s[s.size() - 1]) return vector<int>();
            next_permutation(s.begin(), s.end());
            return s;
        }
};
