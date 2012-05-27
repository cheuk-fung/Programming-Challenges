#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

typedef set<int>::const_iterator sci;

set<int> tri;

bool check(int n)
{
    for (sci it = tri.begin(); it != tri.end(); it++) {
        if (tri.count(n - *it)) return true;
    }
    return false;
}

int main()
{
    for (long long k = 1; k * (k + 1) / 2 <= 1000000000; k++) {
        tri.insert(k * (k + 1) / 2);
    }

    int n;
    while (cin >> n) {
        puts(check(n) ? "YES" : "NO");
    }

    return 0;
}

