#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a, b, r;
    cin >> a >> b >> r;
    if (min(a, b) < 2 * r) puts("Second");
    else puts("First");

    return 0;
}

