#include <iostream>
#include <string>
using namespace std;

string presidents[] = {
    "Washington",
    "Adams",
    "Jefferson",
    "Madison",
    "Monroe",
    "Adams",
    "Jackson",
    "Van Buren",
    "Harrison",
    "Tyler",
    "Polk",
    "Taylor",
    "Fillmore",
    "Pierce",
    "Buchanan",
    "Lincoln",
    "Johnson",
    "Grant",
    "Hayes",
    "Garfield",
    "Arthur",
    "Cleveland",
    "Harrison",
    "Cleveland",
    "McKinley",
    "Roosevelt",
    "Taft",
    "Wilson",
    "Harding",
    "Coolidge",
    "Hoover",
    "Roosevelt",
    "Truman",
    "Eisenhower",
    "Kennedy",
    "Johnson",
    "Nixon",
    "Ford",
    "Carter",
    "Reagan",
    "Bush",
    "Clinton",
    "Bush",
    "Obama"
};

int main()
{
    int a;
    cin >> a;
    cout << presidents[a - 1] << endl;

    return 0;
}
