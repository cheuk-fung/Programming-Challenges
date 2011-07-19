/*
 *  SRC: POJ 3250
 * PROB: Bad Hair Day
 * ALGO: stack
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <stack>

using std::stack;

int n;
long long h[80000], cnt[80000];
stack<int> S;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", h + i);

    for (int i = n - 1; i >= 0; i--) {
        while (!S.empty() && h[i] > h[S.top()]) {
            cnt[i] += cnt[S.top()] + 1;
            S.pop();
        }
        S.push(i);
    }

    long long tot = 0;
    for (int i = 0; i < n; i++)
        tot += cnt[i];

    printf("%lld\n", tot);

    return 0;
}
