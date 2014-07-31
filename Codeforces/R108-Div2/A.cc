#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int n, m;
string stu[110];

bool check(int p)
{
    for (int k = 0; k < m; k++) {
        bool flag = true;
        for (int i = 0; i < n; i++)
            if (stu[i][k] > stu[p][k]) flag = false;
        if (flag) return true;
    }
    return false;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> stu[i];

    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (check(i)) cnt++;

    cout << cnt << endl;

    return 0;
}

