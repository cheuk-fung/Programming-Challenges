#include <iostream>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    set<int> levels;

    int p;
    cin >> p;
    for (int i = 0; i < p; i++) {
        int a;
        cin >> a;
        levels.insert(a);
    }

    cin >> p;
    for (int i = 0; i < p; i++) {
        int a;
        cin >> a;
        levels.insert(a);
    }

    if (levels.size() == (size_t) n) {
        cout << "I become the guy." << endl;
    } else {
        cout << "Oh, my keyboard!" << endl;
    }

    return 0;
}
