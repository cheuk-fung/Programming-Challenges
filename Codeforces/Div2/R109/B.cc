#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Card {
    int a, b;

    Card(int _a, int _b) : a(_a), b(_b) { }

    bool operator <(const Card &other) const
    {
        if (b == other.b) return a > other.a;
        return b > other.b;
    }
};
vector<Card> c;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        c.push_back(Card(a, b));
    }

    sort(c.begin(), c.end());

    int ans = 0, cnt = 1;
    for (vector<Card>::const_iterator it = c.begin(); cnt && it != c.end(); it++, cnt--) {
        ans += it->a;
        cnt += it->b;
    }

    cout << ans << endl;

    return 0;
}

