#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int tux;
    cin >> tux;
    int foo = 0;
    int bar = 0;
    int baz = 0;
    int quz = 1;
    for (int i = 0; i < tux; i++) {
        int pur;
        cin >> pur;
        foo = foo + pur;
        bar = bar + 1;
        if (max(foo * quz, bar * baz) == foo * quz) {
            baz = foo;
            quz = bar;
        }
    }
    printf("%.10f\n", baz * 1.0 / quz);

    return 0;
}
