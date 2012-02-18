#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Friend {
    int s;
    string name;
    vector<string> num;

    int taxi, piz, girl;
} fri[200];

int max_num;
vector<string> max_fri;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> fri[i].s >> fri[i].name;
        string num;
        for (int j = 0; j < fri[i].s; j++) {
            cin >> num;
            fri[i].num.push_back(num);
        }
    }

    for (int i = 0; i < n; i++) {
        int taxi = 0, piz = 0;
        for (int j = 0; j < fri[i].s; j++) {
            string num = fri[i].num[j];
            if (num[0] == num[1]  && num[1] == num[3] && num[3] == num[4] && num[4] == num[6] && num[6] == num[7]) taxi++;
            if (num[0] > num[1]  && num[1] > num[3] && num[3] > num[4] && num[4] > num[6] && num[6] > num[7]) piz++;
        }
        fri[i].taxi = taxi;
        fri[i].piz = piz;
        fri[i].girl = fri[i].s - taxi - piz;
    }

    for (int i = 0; i < n; i++) {
        if (fri[i].taxi > max_num) {
            max_num = fri[i].taxi;
            max_fri.clear();
            max_fri.push_back(fri[i].name);
        }
        else if (fri[i].taxi == max_num) {
            max_fri.push_back(fri[i].name);
        }
    }
    cout << "If you want to call a taxi, you should call: ";
    for (int i = 0; i < max_fri.size() - 1; i++) cout << max_fri[i] << ", ";
    cout << max_fri[max_fri.size() - 1] << ".\n";

    max_num = 0;
    max_fri.clear();
    for (int i = 0; i < n; i++) {
        if (fri[i].piz > max_num) {
            max_num = fri[i].piz;
            max_fri.clear();
            max_fri.push_back(fri[i].name);
        }
        else if (fri[i].piz == max_num) {
            max_fri.push_back(fri[i].name);
        }
    }
    cout << "If you want to order a pizza, you should call: ";
    for (int i = 0; i < max_fri.size() - 1; i++) cout << max_fri[i] << ", ";
    cout << max_fri[max_fri.size() - 1] << ".\n";

    max_num = 0;
    max_fri.clear();
    for (int i = 0; i < n; i++) {
        if (fri[i].girl > max_num) {
            max_num = fri[i].girl;
            max_fri.clear();
            max_fri.push_back(fri[i].name);
        }
        else if (fri[i].girl == max_num) {
            max_fri.push_back(fri[i].name);
        }
    }
    cout << "If you want to go to a cafe with a wonderful girl, you should call: ";
    for (int i = 0; i < max_fri.size() - 1; i++) cout << max_fri[i] << ", ";
    cout << max_fri[max_fri.size() - 1] << ".\n";

    return 0;
}

