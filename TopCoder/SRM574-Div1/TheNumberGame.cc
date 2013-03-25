#include <algorithm>
#include <string>

using namespace std;

class TheNumberGame {
    private:
        string toString(int x)
        {
            string s;
            while (x) {
                s += '0' + x % 10;
                x /= 10;
            }
            return s;
        }

    public:
        string determineOutcome(int A, int B)
        {
            string AS = toString(A), BS = toString(B);
            if (AS.find(BS) != string::npos) return "Manao wins";
            reverse(AS.begin(), AS.end());
            if (AS.find(BS) != string::npos) return "Manao wins";

            return "Manao loses";
        }
};
