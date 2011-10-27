/*
 *  SRC: POJ 2794
 * PROB: Double Patience
 * ALGO: DP
 * DATE: Aug 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <stack>

using std::stack;

const int MAX_N = 1953125;

stack<char> cards[9];
int vis[MAX_N];
double f[MAX_N];

int encode()
{
    int res = 0;
    for (int i = 0; i < 9; i++)
        res = res * 5 + cards[i].size();
    return res;
}

double work()
{
    int code = encode();
    if (vis[code]) return f[code];
    vis[code] = 1;

    double res = 0.0;
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (cards[i].empty()) continue;
        for (int j = i + 1; j < 9; j++) {
            if (cards[j].empty()) continue;
            if (cards[i].top() == cards[j].top()) {
                cnt++;

                char t = cards[i].top();
                cards[i].pop();
                cards[j].pop();

                res += work();

                cards[i].push(t);
                cards[j].push(t);
            }
        }
    }

    if (!cnt) return 0.0;
    return f[code] = res / cnt;
}

int main()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 4; j++) {
            char s[5];
            scanf("%s", s);
            cards[i].push(s[0]);
        }

    vis[0] = 1;
    f[0] = 1.0;
    printf("%.10f\n", work());

    return 0;
}
