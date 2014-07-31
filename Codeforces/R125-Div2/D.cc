#include <iostream>
#include <string>

using namespace std;

int n, k;
string w[2];
bool f[2][100010];

void dp(int water, int wall, int level)
{
    level = min(n, level);
    if (water >= level) return ;
    if (f[wall][level]) return ;
    if (w[wall][level] == 'X') return ;

    f[wall][level] = 1;
    dp(water + 1, wall ^ 1, level + k);
    dp(water + 1, wall, level - 1);
    dp(water + 1, wall, level + 1);
}

int main()
{
    cin >> n >> k;
    cin >> w[0] >> w[1];
    w[0] += '-';
    w[1] += '-';

    dp(-1, 0, 0);
    cout << (f[0][n] || f[1][n] ? "YES" : "NO") << endl;

    return 0;
}

