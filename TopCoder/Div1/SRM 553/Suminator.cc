#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class Suminator {
    private:
        long long getResult(const vector<int> &program)
        {
            stack<long long> s;
            for (int i = 0; i <= SIZE(program); i++) {
                s.push(0);
            }
            for (int i = 0; i < SIZE(program); i++) {
                if (program[i] == 0) {
                    long long a, b;
                    a = s.top();
                    s.pop();
                    b = s.top();
                    s.pop();
                    s.push(a + b);
                } else {
                    s.push(program[i]);
                }
            }
            return s.top();
        }

    public:
        int findMissing(vector <int> program, int wantedResult)
        {
            int pos = find(program.begin(), program.end(), -1) - program.begin();
            program[pos] = 0;
            long long ret = getResult(program);
            if (ret == wantedResult) return 0;

            int l = 1, r = 1000000000;
            while (l < r) {
                int mid = (l + r) >> 1;
                program[pos] = mid;
                ret = getResult(program);
                if (ret >= wantedResult) r = mid;
                else l = mid + 1;
            }
            program[pos] = l;
            ret = getResult(program);
            if (ret == wantedResult) return l;
            return -1;
        }
};
