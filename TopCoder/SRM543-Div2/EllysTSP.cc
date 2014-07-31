#include <cstdio>
#include <string>

using namespace std;

class EllysTSP {
    private:

    public:
        int getMax(string places)
        {
            int v_cnt= 0, c_cnt = 0;
            for (int i = 0; i < places.length(); i++) {
                places[i] == 'V' ? v_cnt++ : c_cnt++;
            }
            return (min(v_cnt, c_cnt) << 1) + (v_cnt != c_cnt);
        }
};
