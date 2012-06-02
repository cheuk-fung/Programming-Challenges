#include <vector>
#include <string>

using namespace std;

class ElectionFraudDiv2 {
    private:

    public:
        string IsFraudulent(vector <int> percentages)
        {
            int low = 0, high = 0;
            for (int i = 0; i < percentages.size(); i++) {
                low += percentages[i] * 100;
                if (percentages[i] > 0) low -= 50;

                high += percentages[i] * 100;
                if (percentages[i] < 100) high += 49;
            }
            if (low > 10000 || high < 10000) return "YES";
            return "NO";
        }
};

