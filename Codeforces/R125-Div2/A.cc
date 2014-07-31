#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<long long> F;
    F.push_back(0);
    F.push_back(1);
    for (int i = 1; F[i] + F[i - 1] <= 1000000000; i++)
        F.push_back(F[i] + F[i - 1]);

    int n;
    cin >> n;
    for (int i = 0; i < F.size(); i++)
        for (int j = 0; j < F.size(); j++)
            for (int k = 0; k < F.size(); k++)
                if (F[i] + F[j] + F[k] == n) {
                    cout << F[i] << ' ' << F[j] << ' ' << F[k] << endl;
                    return 0;
                }
    cout << "I'm too stupid to solve this problem" << endl;

    return 0;
}

